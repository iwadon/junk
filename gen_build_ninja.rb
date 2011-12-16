require 'pp'
require 'yaml'

class NinjaGenerator
  class << self
    def generate_from_yaml(yaml)
      b = new
      h = YAML.load(yaml)
      h.each do |k, v|
        (v || []).each do |vk, vv|
          b.__send__("add_#{k}", vk, vv)
        end
      end
      b.generate
    end
  end

  def initialize
    @vars = {}
    @rules = {}
    @builds = {}
    add_rule 'cxx', description: 'CXX $out', command: '$cxx -MMD -MF $out.d $cxxflags $cppflags -o $out -c $in', depfile: '$out.d'
    add_rule 'link', description: 'LINK $out', command: '$cxx $ldflags -o $out $in $libs'
    add_rule 'ar', description: 'AR $out', command: '$ar crs $out $in'
  end

  def add_var(name, value)
    @vars[name] = value
  end

  def add_rule(name, value)
    @rules[name] = value
  end

  def add_program(name, value)
    rule = value.delete('rule') || value.delete(:rule) || 'link'
    value[rule] = extract_objs(name, value)
    add_build(name, value)
  end

  def add_library(name, value)
    rule = value.delete('rule') || value.delete(:rule) || 'ar'
    value[rule] = extract_objs(name, value)
    add_build(name, value)
  end

  def add_misc(name, value)
    rule = value.delete('rule') || value.delete(:rule)
    value[rule] = extract_src(value)
    add_build(name, value)
  end

  def add_build(name, value)
    @builds[name] = value
  end

  def extract_objs(name, value)
    prefix = File.basename(name)
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
    text
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
end

if __FILE__ == $0
  require 'erb'
  require 'optparse'
  def usage
    puts(ARGV.options)
    exit(1)
  end
  opt = Struct.new(:cc, :cxx, :cflags, :cppflags, :cxxflags, :debug, :inline, :optimize, :prefix, :configure_args).new
  opt.prefix = if /darwin/ =~ RUBY_PLATFORM
                 '/Users/don/local'
               else
                 '/usr/local'
               end
  def opt.get_binding
    binding
  end
  opt.configure_args = []
  opt.cc = 'gcc'
  opt.cxx = 'g++'
  ARGV.options do |q|
    q.on('--prefix=DIR', 'specify prefix') do |v|
      opt.prefix = v
    end
    q.on('--[no-]debug', '-d', 'enable/disable options for debugging') do |v|
      opt.debug = v
    end
    q.on('--[no-]optimize', '-O', 'enable/disable options for optimizing') do |v|
      opt.optimize = v
    end
    q.on('--[no-]inline', '-i', 'enable/disable inline functions') do |v|
      opt.inline = v
    end
    q.on('--with-clang', 'compile with clang') do
      opt.cc = 'clang'
      opt.cxx = 'clang++'
    end
    q.on('--with-gcc', 'compile with/without gcc') do
      opt.cc = 'gcc'
      opt.cxx = 'g++'
    end
    q.parse!
  end || usage
  usage if ARGV.empty?
  opt.configure_args << '--prefix=$prefix'
  opt.cflags ||= '-Wall -Wextra'
  opt.cxxflags ||= '-Wall -Wextra'
  if opt.debug
    opt.cflags += ' -g'
    opt.cxxflags += ' -g'
    opt.configure_args << "--debug"
  else
    opt.configure_args << "--no-debug"
  end
  if opt.optimize
    opt.cflags += ' -O2'
    opt.cxxflags += ' -O2'
    opt.configure_args << "--optimize"
  else
    opt.cflags += ' -O0'
    opt.cxxflags += ' -O0'
    opt.configure_args << "--no-optimize"
  end
  opt.cppflags ||= ''
  if /darwin/ =~ RUBY_PLATFORM
    opt.cppflags += ' -DHAVE_MACH_MACH_TIME_H'
  end
  if opt.inline
    opt.cppflags += ' -DSHOOTER_INLINE=inline'
    opt.configure_args << "--inline"
  else
    opt.configure_args << "--no-inline"
  end
  opt.configure_args = opt.configure_args.join(' ')
  def process(file, opt)
    orig_file = file
    text = File.read(file)
    loop do
      ext = File.extname(file)
      base = File.join(File.dirname(file), File.basename(file, ext))
      case ext
      when /\.erb\z/i
        text = ERB.new(text).result(opt.get_binding)
      when /\.yaml\z/i
        text = NinjaGenerator.generate_from_yaml(text)
      else
        File.open(file, 'w') do |f|
          f.flock(File::LOCK_EX)
          f.write(text)
          f.puts(<<EOS)

configure_args = #{opt.configure_args}
rule configure
  command = ruby #{$0} $in $configure_args
  generator = 1
build #{file}: configure #{orig_file} | #{$0}
EOS
        end
        return
      end
      file = base
    end
  end
  ARGV.each do |arg|
    process(arg, opt)
  end
end
