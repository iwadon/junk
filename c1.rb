# echo client
require 'socket'
TCPSocket.open('localhost', 7777) do |sock|
  while str = gets
    sock.print(str)
    puts(sock.gets)
  end
end
