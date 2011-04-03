#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

static const int PORT = 7777;

int main(int argc, char *argv[])
{
  int ret;
  int sock;
  struct sockaddr_in addr;
  int yes = 1;

  ret = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (ret == -1) {
    perror("socket");
    return 1;
  }
  sock = ret;

  if (argc != 1) {
    ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &yes, sizeof yes);
    if (ret == -1) {
      perror("setsockopt");
      ret = close(sock);
      if (ret == -1) {
	perror("close");
      }
      return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    addr.sin_port = htons(PORT);
    ret = sendto(sock, "Hello", 5, 0, (struct sockaddr *)&addr, sizeof addr);
    if (ret == -1) {
      perror("sendto");
      close(sock);
      return 1;
    }
  } else {
    char buf[2048];

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    ret = bind(sock, (struct sockaddr *)&addr, sizeof addr);
    if (ret == -1) {
      perror("bind");
      close(sock);
      return 1;
    }

    memset(buf, 0, sizeof buf);
    ret = recv(sock, buf, sizeof buf, 0);
    if (ret == -1) {
      perror("recv");
      close(sock);
      return 1;
    }

    puts(buf);
  }

  ret = close(sock);
  if (ret == -1) {
    perror("close");
    return 1;
  }

  return 0;
}
