require 'pp'
require 'yaml'

class Ninja
  class << self
    def generate_from_yaml(yaml)
      b = new
      h = YAML.load(yaml)
      h.each do |k, v|
        v.each do |vk, vv|
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
    objs = value.delete('src') || value.delete(:src)
    flags = {}
    value.keys.grep(/\Acxxflags|cppflags\Z/i).each do |n|
      flags[n] = value.delete(n)
    end
    objs.map! do |i|
      case i
      when /\A(.+)\.(cpp|cxx|cc)\Z/i
        obj = $1 + '.o'
        add_build(obj, {cxx: i}.merge(flags))
        obj
      else
        i
      end
    end
    value['link'] = objs
    add_build(name, value)
  end

  def add_library(name, value)
    objs = value.delete('src') || value.delete(:src)
    flags = {}
    value.keys.grep(/\Acxxflags|cppflags\Z/i).each do |n|
      flags[n] = value.delete(n)
    end
    objs.map! do |i|
      case i
      when /\A(.+)\.(cpp|cxx|cc)\Z/i
        obj = $1 + '.o'
        add_build(obj, {cxx: i}.merge(flags))
        obj
      else
        i
      end
    end
    value['ar'] = objs
    add_build(name, value)
  end

  def add_build(name, value)
    @builds[name] = value
  end

  def generate
    text = ''
    @vars.each do |k, v|
      text << "#{k} = #{v}\n"
    end
    @rules.each do |k, v|
      text << "rule #{k}\n"
      v.each do |vk, vv|
        text << "  #{vk} = #{vv}\n"
      end
    end
    @builds.each do |k, v|
      rule = (v.keys.map(&:to_s) & @rules.keys.map(&:to_s)).first
      raise "rule is missing?" if rule.nil?
      srcs = v.delete(rule.intern) || v.delete(rule.to_s)
      srcs = [srcs] unless Array === srcs
      text << "build #{k}: #{rule} #{srcs.join(' ')}\n"
      v.each do |vk, vv|
        text << "  #{vk} = #{vv}\n"
      end
    end
    text
  end
end

if __FILE__ == $0
  text = Ninja.generate_from_yaml(File.read(ARGV[0]))
  File.open(ARGV[0].sub(/\.ya?ml\Z/i, ''), 'w') do |f|
    f.flock(File::LOCK_EX)
    f.write(text)
  end
end
