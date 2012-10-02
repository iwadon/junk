/**
 * @file addrinfo.cpp
 * @brief Addrinfoクラスの実装
 */

#include "addrinfo.hpp"
#include "socket.hpp"
#include <cstring>
#include <cstdlib>
#include <unistd.h>

namespace
{

  const char *family_string(const int family)
  {
    switch (family) {
    case PF_INET:
      return "INET4";
    case PF_INET6:
      return "INET6";
    default:
      return "";
    }
  }

  const char *socktype_string(const int socktype)
  {
    switch (socktype) {
    case SOCK_STREAM:
      return "STREAM";
    case SOCK_DGRAM:
      return "DGRAM";
    default:
      return "";
    }
  }

  const char *protocol_string(const int protocol)
  {
    switch (protocol) {
    case IPPROTO_TCP:
      return "TCP";
    case IPPROTO_UDP:
      return "UDP";
    default:
      return "";
    }
  }

  std::string sockaddr_in_string(const sockaddr_in *sin)
  {
    if (sin != NULL) {
      char buf[128];
      if (inet_ntop(sin->sin_family, &sin->sin_addr, buf, sizeof buf) == NULL) {
	perror("inet_ntop() failed");
	return "";
      }
      char buf2[128];
      uint16_t port = ntohs(sin->sin_port);
      if (port != 0) {
	snprintf(buf2, sizeof buf2, "%s:%d", buf, port);
	return buf2;
      } else {
	return buf;
      }
    } else {
      return "";
    }
  }

  std::string addrinfo_string(const addrinfo *ai)
  {
    if (ai != NULL) {
      std::string str("");
      if (ai->ai_family != 0) {
	str += family_string(ai->ai_family);
      }
      if (ai->ai_socktype) {
	if (ai->ai_family != 0) {
	  str += " ";
	}
	str += socktype_string(ai->ai_socktype);
      }
      if (ai->ai_protocol) {
	if (ai->ai_family != 0 || ai->ai_socktype) {
	  str += " ";
	}
	str += protocol_string(ai->ai_protocol);
      }
      return str;
    } else {
      return "";
    }
  }

  void setup_addrinfo(addrinfo &ai, const int family, const int socktype, const int protocol, const int flags)
  {
    memset(&ai, 0, sizeof (addrinfo));
    ai.ai_flags = flags;
    ai.ai_family = family;
    ai.ai_socktype = socktype;
    ai.ai_protocol = protocol;
  }

  char *serv_by_port(const int port, const char *protocol)
  {
    char *result = NULL;
    servent *se = getservbyport(htons(port), protocol);
    if (se != NULL) {
      result = strdup(se->s_name);
    } else {
      static const size_t RESULT_BUFSIZ = 12;
      result = reinterpret_cast<char *>(malloc(RESULT_BUFSIZ));
      if (result == NULL) {
	perror("malloc() failed");
	return NULL;
      }
      snprintf(result, RESULT_BUFSIZ, "%10d", port);
    }
    return result;
  }

} // unnamed namespace

std::vector<Addrinfo *> Addrinfo::getaddrinfo(const char *host, const char *serv, const int family, const int socktype, const int protocol, const int flags)
{
  addrinfo hints;
  setup_addrinfo(hints, family, socktype, protocol, flags);
  addrinfo *res0;
  std::vector<Addrinfo *> v;
  int ret = ::getaddrinfo(host, serv, &hints, &res0);
  if (ret == 0) {
    for (addrinfo *res = res0; res != NULL; res = res->ai_next) {
      Addrinfo *ai = new Addrinfo(res);
      v.push_back(ai);
    }
  }
  freeaddrinfo(res0);
  return v;
}

std::vector<Addrinfo *> Addrinfo::getaddrinfo(const char *host, const int port, const int family, const int socktype, const int protocol, const int flags)
{
  char *serv = serv_by_port(port, NULL);
  if (serv != NULL) {
    std::vector<Addrinfo *> v(getaddrinfo(host, serv, family, socktype, protocol, flags));
    free(serv);
    return v;
  } else {
    std::vector<Addrinfo *> v;
    return v;
  }
}

static Addrinfo *new_addrinfo(const int pfamily, const int socktype, const int protocol, const char *host, const char *serv)
{
  addrinfo hints;
  setup_addrinfo(hints, pfamily, socktype, protocol, 0);
  addrinfo *res0;
  int ret = ::getaddrinfo(host, serv, &hints, &res0);
  Addrinfo *ai = NULL;
  if (ret == 0) {
    ai = new Addrinfo(res0);
  }
  freeaddrinfo(res0);
  return ai;
}

Addrinfo *Addrinfo::tcp(const char *host, const int port)
{
  char *serv = serv_by_port(port, "tcp");
  if (serv == NULL) {
    return NULL;
  }
  Addrinfo *ai = tcp(host, serv);
  free(serv);
  return ai;
}

Addrinfo *Addrinfo::tcp(const char *host, const char *serv)
{
  return new_addrinfo(PF_INET, SOCK_STREAM, IPPROTO_TCP, host, serv);
}

Addrinfo *Addrinfo::udp(const char *host, const int port)
{
  char *serv = serv_by_port(port, "udp");
  if (serv == NULL) {
    return NULL;
  }
  Addrinfo *ai = udp(host, serv);
  free(serv);
  return ai;
}

Addrinfo *Addrinfo::udp(const char *host, const char *serv)
{
  return new_addrinfo(PF_INET, SOCK_DGRAM, IPPROTO_UDP, host, serv);
}

/**
 * @brief コンストラクタ
 *
 * @param [in] ai アドレス情報。
 */
Addrinfo::Addrinfo(const addrinfo *ai)
  : ai_(NULL)
{
  void *p = malloc(sizeof (addrinfo));
  if (p != NULL) {
    memcpy(p, ai, sizeof (addrinfo));
    ai_ = reinterpret_cast<addrinfo *>(p);
    p = malloc(ai->ai_addrlen);
    if (p != NULL) {
      memcpy(p, ai->ai_addr, ai->ai_addrlen);
      sockaddr *addr = reinterpret_cast<sockaddr *>(p);
      ai_->ai_addr = addr;
      if (ai->ai_canonname != NULL) {
	ai_->ai_canonname = strdup(ai->ai_canonname);
      }
      ai_->ai_next = NULL;
    } else {
      free(ai_);
      ai_ = NULL;
    }
  }
}

Addrinfo::Addrinfo(const sockaddr_in *sin)
  : ai_(NULL)
{
  void *p = malloc(sizeof (addrinfo));
  if (p != NULL) {
    memset(p, 0, sizeof (addrinfo));
    ai_ = reinterpret_cast<addrinfo *>(p);
    ai_->ai_family = sin->sin_family;
    ai_->ai_addrlen = sizeof (sockaddr_in);
    p = malloc(sizeof (sockaddr_in));
    if (p != NULL) {
      memcpy(p, sin, sizeof (sockaddr_in));
      sockaddr *addr = reinterpret_cast<sockaddr *>(p);
      ai_->ai_addr = addr;
    } else {
      free(ai_);
      ai_ = NULL;
    }
  }
}

Addrinfo::~Addrinfo()
{
  if (ai_ != NULL) {
    free(ai_->ai_canonname);
    free(ai_->ai_addr);
  }
  free(ai_);
}

Socket *Addrinfo::bind()
{
  int sock = socket(pfamily(), socktype(), protocol());
  if (sock == -1) {
    perror("socket() failed");
    return NULL;
  }
#if 1
  int ok = 1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof ok) != 0) {
    perror("setsockopt() failed");
    close(sock);
    return NULL;
  }
#endif
  int ret = ::bind(sock, addr(), addrlen());
  if (ret != 0) {
    perror("bind() failed");
    close(sock);
    return NULL;
  }
  return new Socket(sock);
}

Socket *Addrinfo::connect()
{
  int sock = socket(pfamily(), socktype(), protocol());
  if (sock == -1) {
    perror("socket() failed");
    return NULL;
  }
  int ret = ::connect(sock, addr(), addrlen());
  if (ret != 0) {
    perror("connect() failed");
    close(sock);
    return NULL;
  }
  return new Socket(sock);
}

std::string Addrinfo::inspect() const
{
  std::string str("#<Addrinfo");
  if (ai_ != NULL) {
    str += ":";
    if (ai_->ai_addr != NULL) {
      str += " ";
      str += sockaddr_in_string(addr_in());
    }
    if (ai_->ai_protocol) {
      str += " ";
      str += protocol_string(ai_->ai_protocol);
    }
  }
  str += ">";
  return str;
}
