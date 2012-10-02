/**
 * @file  addrinfo.hpp
 * @brief Addrinfoクラスの実装
 */

#ifndef ADDRINFO_HPP_INCLUDED
#define ADDRINFO_HPP_INCLUDED 1

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <vector>

class Socket;

/**
 * @class Addrinfo
 * @brief getaddrinfo()/freeaddrinfo()のラッパー
 */
class Addrinfo
{
public:
  static std::vector<Addrinfo *> getaddrinfo(const char *host, const char *serv, const int family = PF_UNSPEC, const int socktype = 0, const int protocol = 0, const int flags = 0);
  static std::vector<Addrinfo *> getaddrinfo(const char *host, const int port, const int family = PF_UNSPEC, const int socktype = 0, const int protocol = 0, const int flags = 0);
  static Addrinfo *tcp(const char *host, const char *serv);
  static Addrinfo *tcp(const char *host, const int port);
  static Addrinfo *udp(const char *host, const char *serv);
  static Addrinfo *udp(const char *host, const int port);
  Addrinfo(const addrinfo *ai);
  Addrinfo(const sockaddr_in *ai);
  ~Addrinfo();
  int flags() const { return ai_->ai_flags; }
  int pfamily() const { return ai_->ai_family; }
  int socktype() const { return ai_->ai_socktype; }
  int protocol() const { return ai_->ai_protocol; }
  socklen_t addrlen() const { return ai_->ai_addrlen; }
  sockaddr *addr() const { return ai_->ai_addr; }
  sockaddr_in *addr_in() const { return reinterpret_cast<sockaddr_in *>(ai_->ai_addr); }
  Socket *bind();
  Socket *connect();
  std::string inspect() const;
private:
  addrinfo *ai_;
};

#include <ostream>
static inline std::ostream &operator<<(std::ostream &os, const Addrinfo &ai)
{
  os << ai.inspect();
  return os;
}

#endif // !defined(ADDRINFO_HPP_INCLUDED)
