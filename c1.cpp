#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef STDCXX_98_HEADERS
#include <cstdio>
#include <cstring>
#endif
#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#include <sys/socket.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

int main(int /*argc*/, char */*argv*/[])
{
  int sock;
  sockaddr_in addr;
  static const size_t BUF_SIZE = 256;
  char buf[BUF_SIZE];
  size_t len;
  ssize_t recv_len;

  sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock == -1) {
    perror("socket() failed");
    return 1;
  }

  memset(&addr, 0, sizeof addr);
  addr.sin_family = AF_INET;
  inet_aton("127.0.0.1", &addr.sin_addr);
  addr.sin_port = htons(7777);

  if (connect(sock, reinterpret_cast<sockaddr *>(&addr), sizeof addr) < 0) {
    perror("connect() failed");
    return 1;
  }

  while (true) {
    if (fgets(buf, BUF_SIZE, stdin) == NULL) {
      break;
    }
    len = strlen(buf);
    if (send(sock, buf, len, 0) == -1) {
      perror("send() failed");
      return 1;
    }
    
    recv_len = recv(sock, buf, BUF_SIZE, 0);
    if (recv_len == -1) {
      perror("recv() failed");
      return 1;
    }
    buf[recv_len] = '\0';
    if (fputs(buf, stdout) == EOF) {
      perror("fputs() failed");
      return 1;
    }
  }

  if (close(sock) == -1) {
    perror("close() failed");
    return 1;
  }

  return 0;
}
