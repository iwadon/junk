# echo server
require 'socket'
Socket.tcp_server_loop(7777) do |client_sock, client_addrinfo|
  p([client_sock, client_addrinfo])
  begin
    while str = client_sock.gets
      puts(str)
      client_sock.print(str)
    end
  ensure
    client_sock.close
    puts("[#{client_addrinfo.inspect} is gone.]")
  end
end
