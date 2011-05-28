require 'optparse'

def usage
  puts(ARGV.options)
  exit(1)
end

git = 'git'
wait_time = 3
build = 'make check'

ARGV.options do |q|
  q.on('-c CMDLINE', String, "build command (default: #{build}") do |v|
    build = v
  end
  q.on('-g GIT', String, "git command (default: #{git})") do |v|
    git = v
  end
  q.on('-t SEC', Integer, "wait time (default: #{wait_time})") do |v|
    wait_time = v
  end
  q.parse!
end || usage

files = {}

loop do
  prev_files = files
  files = {}
  git_result = `#{git} ls-files ..`.split
  git_result.each do |file|
    files[file] = {:mtime => File.mtime(file)}
  end
  new_files = files.keys - prev_files.keys
  removed_files = prev_files.keys - files.keys
  updated_files = prev_files.keys.select do |k|
    prev_files[k][:mtime] != files[k][:mtime]
  end
  updated = new_files + removed_files + updated_files
  files.each do |file, info|
    t = File.mtime(file)
    if t != info[:mtime]
      info[:mtime] = t
      updated << file
    end
  end
  unless updated.empty?
    STDERR.puts(" Updated #{updated.size} file(s)")
    system(build)
  end
  #STDERR.putc('.')
  sleep wait_time
end
