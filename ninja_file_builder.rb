require 'erb'
require 'optparse'
require 'ostruct'
require 'yaml'

class NinjaFileBuilder
  attr_reader :options

  def initialize
    @options = OpenStruct.new
    @options.prefix = '/usr/local'
    @options.input_file = 'build.ninja.yaml.erb'
    @options.cc = 'gcc'
    @options.cflags = ''
    @options.cxx = 'g++'
    @options.cxxflags = ''
    @options.cppflags = ''
    @options.ar = 'ar'
    @options.ldflags = ''
    @options.libs = ''
    @options.configure_args = ''
    @options.ruby = File.join(RbConfig::CONFIG['bindir'], 'ruby')
    @options.verbose = 0

    @option_parser = OptionParser.new
    @option_parser.banner = "Usage: #{$0} [options] NAME=VALUE ..."
    @option_parser.separator 'Specific options:'
    add_option('--prefix=DIR', 'specify prefix') do |v|
      @options.prefix = v
    end
    add_option('--input-file=FILE', '-i', "specify input file") do |v|
      @options.input_file = v
    end
    add_option('--output-file=FILE', '-o', "specify output file") do |v|
      @options.output_file = v
    end
    add_option('--verbose[=NUM]', '-v', Integer, 'verbose level') do |v|
      if v
        options.verbose = v
      else
        options.verbose += 1
      end
    end

    @vars = {}
    @rules = {}
    @builds = {}
    @defaults = []
  end

  def self.build(&block)
    self.new.instance_eval(&block)
  end

  def add_option(*args, &block)
    name = nil
    args.each do |arg|
      if /\A(--?[\-\+\w]+)=?/ =~ arg
        name = $1
        break
      end
    end
    b = Proc.new do |v|
      block.call(v)
      @options.configure_args += " #{name}"
      case v
      when Integer, String
        if /\s+/ =~ v.to_s
          v = "\"#{v}\""
        end
        @options.configure_args += "=#{v}"
      end
    end
    @option_parser.on(*args, &b)
  end

  def parse_args
    @option_parser.parse!
    ARGV.each do |arg|
      case arg
      when /\A(\w+)\z/
        @options.configure_args += " #{arg}"
      when /\A(\w+)=(.+)\z/
        k, v = $1, $2
        @options.send("#{k}=", v)
        v = "\"#{v}\"" if /\s+/ =~ v
        @options.configure_args += " #{k}=#{v}"
      end
    end
  end

  def save_ninja_file
    file = @options.input_file
    orig_file = file
    text = File.read(file)
    loop do
      ext = File.extname(file)
      base = File.join(File.dirname(file), File.basename(file, ext))
      case ext
      when /\.erb\z/i
        log 1, "Processing #{file}..."
        text = ERB.new(text).result(@options.instance_eval('binding'))
      when /\.yaml\z/i
        log 1, "Processing #{file}..."
        text = generate_from_yaml(text)
      else
        file = @options.output_file || file
        log 1, "Writing #{file}..."
        File.open(file, 'w') do |f|
          f.flock(File::LOCK_EX)
          f.write(text)
          f.puts(<<EOS)

configure_args = #{@options.configure_args}
rule configure
  description = CONFIGURE build.ninja
  command = #{@options.ruby} #{$0} $in $configure_args
  generator = 1
build #{file}: configure #{orig_file} | #{$0}
EOS
        end
        return
      end
      file = base
    end
  end

  private

  def generate_from_yaml(text)
    h = YAML.load(text)
    h.each do |k, v|
      (v || []).each do |vk, vv|
        __send__("add_#{k}", vk, vv)
      end
    end
    generate
  end

  def generate
    text = ''
    @vars.each do |k, v|
      text << "#{k} = #{v}\n"
    end
    text << "\n"
    @rules.each do |k, v|
      text << "rule #{k}\n"
      v.each do |vk, vv|
        text << "  #{vk} = #{vv}\n"
      end
    end
    text << "\n"
    @builds.each do |k, v|
      rule = (v.keys.map(&:to_s) & @rules.keys.map(&:to_s)).first
      raise "missing rule: #{v.keys.join(', ')}" if rule.nil?
      srcs = extract_array(v, rule)
      implicits = extract_array(v, 'implicit')
      text << "build #{k}: #{rule}"
      text << " #{srcs.join(' ')}" unless srcs.empty?
      text << " | #{implicits.join(' ')}" unless implicits.empty?
      text << "\n"
      v.each do |vk, vv|
        text << "  #{vk} = #{vv}\n"
      end
    end
    unless @defaults.empty?
      text << "\ndefault #{@defaults.join(' ')}\n"
    end
    text
  end

  def add_var(name, value)
    @vars[name] = value
    log 2, "VAR #{name}=#{value.inspect}"
  end

  def add_rule(name, value)
    @rules[name] = value
    log 2, "RULE #{name}=#{value.inspect}"
  end

  def add_program(name, value)
    rule = value.delete('rule') || value.delete(:rule) || 'link'
    value[rule] = extract_objs(name, value)
    add_build(name, value)
    log 2, "PROGRAM #{name}=#{value.inspect}"
  end

  def add_library(name, value)
    rule = value.delete('rule') || value.delete(:rule) || 'ar'
    value[rule] = extract_objs(name, value)
    add_build(name, value)
    log 2, "LIBRARY #{name}=#{value.inspect}"
  end

  def add_misc(name, value)
    rule = value.delete('rule') || value.delete(:rule)
    value[rule] = extract_src(value)
    add_build(name, value)
    log 2, "MISC #{name}=#{value.inspect}"
  end

  def add_default(name, value)
    @defaults << name
    log 2, "DEFAULT #{name}"
  end

  def add_build(name, value)
    @builds[name] = value
  end

  def extract_objs(name, value)
    prefix = File.basename(name).gsub(/\./, '_')
    objs = extract_src(value)
    flags = extract_flags(value, /\Ac(xx|pp)?flags/i)
    objs.map! do |i|
      case i
      when /\A(.+)\.c\Z/
        obj = make_obj(prefix, $1)
        add_build(obj, {cc: i}.merge(flags))
        obj
      when /\A(.+)\.(cpp|cxx|cc|C)\Z/
        obj = make_obj(prefix, $1)
        add_build(obj, {cxx: i}.merge(flags))
        obj
      when /\A(.+)\.m\Z/
        obj = make_obj(prefix, $1)
        add_build(obj, {objc: i}.merge(flags))
        obj
      else
        i
      end
    end
    objs
  end

  def make_obj(prefix, _1)
    dir, base = File.dirname(_1), File.basename(_1)
    File.join('$builddir', "#{prefix}-#{base}.o").gsub(%r|/./|, '/')
  end

  def extract_src(value)
    value.delete('src').to_a + value.delete(:src).to_a
  end

  def extract_flags(value, re)
    flags = {}
    value.keys.grep(re).each do |k|
      flags[k] = value.delete(k)
    end
    flags
  end

  def extract(obj, key)
    obj.delete(key.intern) || obj.delete(key.to_s)
  end

  def extract_array(obj, key)
    value = extract(obj, key)
    value = [value] unless Array === value
    value.compact!
    value
  end

  def log(lvl, *args)
    STDERR.puts(*args) if @options.verbose >= lvl
  end
end

if __FILE__ == $0
  class NinjaFileBuilder
    def check_sdl2(*libs)
      options.sdl2_cflags = `sdl2-config --cflags`.chomp
      options.sdl2_libs = `sdl2-config --libs`.chomp
      libs.each do |lib|
        options.sdl2_libs += " -lSDL2_#{lib}"
      end
    end

    def check_boost(*libs)
      options.boost_cppflags = '-I$prefix/include'
      options.boost_libs = '-L$prefix/lib'
      libs.each do |lib|
        options.boost_libs += " -lboost_#{lib}"
      end
    end

    def check_wx
      options.wx_cppflags = `wx-config --cppflags`
      options.wx_libs = `wx-config --libs`
    end
  end

  NinjaFileBuilder.build do
    options.cflags = '-Wall -Wextra'
    options.cxxflags = '-Wall -Wextra'
    options.cppflags = "-I. -I$prefix/include"
    options.ldflags = '-L$prefix/lib'
    libs = ''
    add_option '--debug', '-d', 'enable debug options' do
      options.cflags << ' -g'
      options.cxxflags << ' -g'
    end
    add_option '--optimize', '-O', 'enable optimize options' do |v|
      options.cflags << ' -O2'
      options.cxxflags << ' -O2'
    end
    add_option '--inline', 'enable inline functions' do
      options.cppflags << ' -DSHOOTER_INLINE=inline'
    end
    add_option '--profile', 'enable profile options' do
      options.cflags << ' -coverage'
      options.cxxflags << ' -coverage'
      options.ldflags << ' -coverage'
      options.libs << ' -lgcov'
    end
    add_option '--enable-c++0x', 'enable C++0x' do
      options.cxxflags << ' -std=c++0x'
    end
    add_option '--enable-c++11', 'enable C++11' do
      options.cxxflags << ' -std=c++11'
    end
    add_option '--with-gcc[=SUFFIX]', 'compile with gcc/g++' do |v|
      options.cc = "gcc#{v}"
      options.cxx = "g++#{v}"
      options.ldflags = "-Wl,-rpath,$prefix/lib/gcc#{v}"
    end
    add_option '--with-clang', 'compile with clang/clang++' do |v|
      options.cc = 'clang'
      options.cxx = 'clang++'
    end
    add_option '--with-csa=PATH', 'compile with Clang Static Analyzer' do |v|
      options.cc = File.join(v, 'libexec', 'ccc-analyzer')
      options.cxx = File.join(v, 'libexec', 'c++-analyzer')
    end
    add_option '--with-boost[=LIBS]', 'compile with Boost' do |v|
      libs = (v || '').split(/,/)
      case RUBY_PLATFORM
      when /freebsd/
        options.cflags << ' -pthread'
        options.ldflags << ' -pthread'
      when /darwin/
        options.cppflags << ' -DHAVE_MACH_MACH_TIME_H'
        libs.map! {|lib| "#{lib}-mt"}
      end
      check_boost *libs
    end
    add_option '--with-sdl2[=LIBS]', 'compile with SDL 2' do |v|
      libs = (v || '').split(/,/)
      check_sdl2 *libs
    end
    add_option '--with-wx', 'compile with wxWidgets' do
      check_wx
    end
    parse_args
    save_ninja_file
  end
end
