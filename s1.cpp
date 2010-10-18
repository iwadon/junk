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

  sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock == -1) {
    perror("socket() failed");
    return 1;
  }

  memset(&addr, 0, sizeof addr);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(7777);

  if (bind(sock, reinterpret_cast<sockaddr *>(&addr), sizeof addr) == -1) {
    perror("bind() failed");
    return 1;
  }

  if (listen(sock, 5) == -1) {
    perror("listen() failed");
    return 1;
  }

  while (true) {
    int client_sock;
    ssize_t recv_len;
    client_sock = accept(sock, NULL, NULL);
    if (client_sock == -1) {
      perror("accept() failed");
      return 1;
    }
    puts("Connected.");

    while (true) {
      recv_len = recv(client_sock, buf, BUF_SIZE - 1, 0);
      switch (recv_len) {
      case -1:
	perror("recv() failed");
	return 1;
      case 0:
	puts("Disconnected.");
	break;
      default:
	buf[recv_len] = '\0';
	if (fputs(buf, stdout) == EOF) {
	  perror("fputs() failed");
	  return 1;
	}
      }

      if (send(client_sock, buf, recv_len, 0) == -1) {
	perror("send() failed");
	return 1;
      }
    }
  }

  if (close(sock) == -1) {
    perror("close() failed");
    return 1;
  }

  return 0;
}
