require 'socket'

class S
  def start
    begin
      Socket.tcp_server_loop(7777) do |c|
        p([self, c])
      end
    rescue Errno::EADDRINUSE
      putc('.')
      STDOUT.flush
      sleep(1)
      retry
    end
  end
end

class C
  def start
    a = Addrinfo.tcp('localhost', 7777)
    a.connect do |s|
      p([self, s])
    end
  end
end

if __FILE__ == $0
  if ARGV.empty?
    S.new.start
  else
    C.new.start
  end
end
