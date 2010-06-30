require 'socket'
Socket.tcp_server_loop(7777) do |sock, client_addrinfo|
  p([sock, client_addrinfo])
  begin
    while str = sock.gets
      p str
      sock.puts("ok!")
      exit if /\Aexit!/ =~ str
    end
  ensure
    p sock.close
  end
end
