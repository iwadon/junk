/**
 * @file  socket.hpp
 * @brief Socketクラスの定義
 */

#ifndef SOCKET_HPP_INCLUDED
#define SOCKET_HPP_INCLUDED 1

#include <netinet/in.h>
#include <string>

class Addrinfo;

/**
 * @class Socket
 * @brief BSDソケットのラッパー
 */
class Socket
{
public:
  static bool get_sockaddr_in(sockaddr_in &sin, const int port, const char *host);
  static bool get_sockaddr_in(sockaddr_in &sin, const char *serv, const char *host);
  static Socket *tcp(const char *host, const char *serv);
  static Socket *udp();
  Socket(int sock);
  Socket(const int pfamily, const int socktype, const int protocol);
  ~Socket();
  int connect(const sockaddr *addr, const socklen_t addrlen);
  int listen(int backlog);
  Socket *accept(sockaddr *address, socklen_t *address_len);
  ssize_t recv(void *buffer, size_t length, int flags);
  ssize_t recvfrom(void *buffer, size_t length, int flags, sockaddr *address, socklen_t *address_len);
  ssize_t send(const void *buffer, size_t length, int flags);
  ssize_t sendto(const void *buffer, size_t length, int flags, const sockaddr *dest_addr, socklen_t dest_len);
  std::string inspect() const;
  Addrinfo *local_address() const;
  Addrinfo *remote_address() const;
  bool set_nonblocking_mode(const bool on_off);
  void set_recv_timeout(const uint64_t usec);
private:
  int sock_;
  uint64_t recv_timeout_;
};

#include <ostream>
static inline std::ostream &operator<<(std::ostream &os, const Socket &sock)
{
  os << sock.inspect();
  return os;
}

#endif // !defined(SOCKET_HPP_INCLUDED)
