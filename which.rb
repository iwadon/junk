# Find the executable file.
def which(file)
  return file if File.executable?(file)
  dir = ENV['PATH'].split(/:/).find do |d|
    File.executable?(File.join(d, file))
  end
  dir ? File.join(dir, file) : nil
end

if __FILE__ == $0
  puts(which(ARGV[0]))
end
