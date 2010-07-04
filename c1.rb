require 'socket'
def access(str, n = 1)
  Addrinfo.tcp('localhost', 7777).connect do |sock|
    n.times do
      sock.puts(str)
      p sock.gets
    end
  end
end
access("HELLO", 9)
access("exit!")
