/**
 * @file socket.cpp
 * @brief Socketクラスの実装
 */
#include "socket.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include "addrinfo.hpp"

/**
 * @brief ホスト名とポート番号をもとにsockaddr_in構造体の内容を埋める
 *
 * @param [out] sin  sockaddr_in構造体。
 * @param [in]  port ポート番号。
 * @param [in]  host ホスト名。
 *
 * @retval true  正常に処理できた。
 * @retval false エラーが起きた。
 *
 * @code
 * sockaddr_in sin;
 * Socket::get_sockaddr_in(sin, 80, "moonrock.jp");
 * @endcode
 */
bool Socket::get_sockaddr_in(sockaddr_in &sin, const int port, const char *host)
{
  char buf[12];
  snprintf(buf, sizeof buf, "%d", port);
  return get_sockaddr_in(sin, buf, host);
}

/**
 * @brief ホスト名とサービス名をもとにsockaddr_in構造体の内容を埋める
 *
 * @param [out] sin  sockaddr_in構造体。
 * @param [in]  serv サービス名。NULLまたは空文字列("")ならば"0"を指定したものとみなす。
 * @param [in]  host ホスト名。NULLまたは空文字列("")ならば"0.0.0.0"を指定したものとみなす。
 *
 * @retval true  正常に処理できた。
 * @retval false エラーが起きた。
 *
 * @code
 * sockaddr_in sin;
 * Socket::get_sockaddr_in(sin, "http", "moonrock.jp");
 * @endcode
 */
bool Socket::get_sockaddr_in(sockaddr_in &sin, const char *serv, const char *host)
{
  addrinfo hints;
  memset(&hints, 0, sizeof hints);
  addrinfo *res0;
  if (host == NULL || strlen(host) == 0) {
    host = "0.0.0.0";
  }
  if (serv == NULL || strlen(serv) == 0) {
    serv = "0";
  }
  int ret = getaddrinfo(host, serv, &hints, &res0);
  if (ret != 0) {
    perror("getaddrinfo() failed");
    return false;
  }
  for (addrinfo *res = res0; res != NULL; res = res->ai_next) {
    if (res->ai_family == PF_INET) {
      memcpy(&sin, res->ai_addr, sizeof sin);
      freeaddrinfo(res0);
      return true;
    }
  }
  freeaddrinfo(res0);
  return false;
}

/**
 * @brief TCPで接続済みのソケットを生成する
 *
 * @param [in] host ホスト名。
 * @param [in] serv サービス名。
 *
 * @retval NULL以外 Socketクラスのオブジェクト。
 * @retval NULL     エラーが起きた。
 *
 * @code
 * Socket *sock = Socket::tcp("moonrock.jp", "http");
 * @endcode
 */
Socket *Socket::tcp(const char *host, const char *serv)
{
  sockaddr_in sin;
  if (!get_sockaddr_in(sin, serv, host)) {
    return NULL;
  }
  Socket *sock = new Socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  int ret = sock->connect(reinterpret_cast<sockaddr *>(&sin), sizeof sin);
  if (ret != 0) {
    delete sock;
    return NULL;
  }
  return sock;
}

/**
 * @brief UDPのソケットを生成する
 *
 * @return 生成されたUDPのソケット。
 *
 * @code
 * Socket *sock = Socket::udp();
 * @endcode
 */
Socket *Socket::udp()
{
  Socket *sock = new Socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  return sock;
}

/**
 * @brief コンストラクタ
 *
 * @param [in] sock ソケット。
 */
Socket::Socket(int sock)
  : sock_(sock)
{
}

/**
 * @brief コンストラクタ
 *
 * @param [in] pfamily  プロトコルファミリー。
 * @param [in] socktype ソケットタイプ。
 * @param [in] protocol プロトコル。
 *
 * @code
 * Socket *sock = new Socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // TCP
 * Socket *sock = new Socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);  // UDP
 * @endcode
 */
Socket::Socket(const int pfamily, const int socktype, const int protocol)
  : sock_(-1)
  , recv_timeout_(0)
{
  sock_ = socket(pfamily, socktype, protocol);
}

/// デストラクタ
Socket::~Socket()
{
  if (sock_ != -1) {
    close(sock_);
    sock_ = -1;
  }
}

/**
 * @brief 指定したアドレスに接続する
 *
 * @param [in] addr    接続相手のアドレス。
 * @param [in] addrlen addrの大きさ。
 *
 * @retval  0 接続した。
 * @retval -1 エラーが起きた。
 *
 * @code
 * sockaddr_in sin;
 * Socket::get_sockaddr_in(sin, 80, "moonrock.jp");
 * Socket *sock = new Socket(PF_INET, SOCK_STREAM, 0);
 * sock->connect(sin, sizeof sin);
 * @endcode
 */
int Socket::connect(const sockaddr *addr, const socklen_t addrlen)
{
  int ret = ::connect(sock_, addr, addrlen);
  if (ret == -1) {
    perror("connect() failed");
  }
  return ret;
}

/**
 * @brief バインドされたソケットでコネクション確立要求を待ち受ける
 *
 * @param [in] backlog ある時点でペンディングにできる(キューイングできる)最大コネクション数。
 *
 * @retval  0 正常に処理した。
 * @retval -1 エラーが起きた。
 *
 * @note このコメントはWikipediaのソケット (BSD)でのlistenの説明を元に書いた。
 */
int Socket::listen(int backlog)
{
  int ret = ::listen(sock_, backlog);
  if (ret == -1) {
    perror("listen() failed");
  }
  return ret;
}

Socket *Socket::accept(sockaddr *address, socklen_t *address_len)
{
  int client_sock = ::accept(sock_, address, address_len);
  if (client_sock == -1) {
    perror("accept() failed");
    return NULL;
  }
  Socket *obj = new Socket(client_sock);
  return obj;
}

/**
 * @brief データを受信する
 *
 * @param [out] buffer 受信したデータを格納するバッファ。
 * @param [in]  length bufferの長さ(バイト単位)。
 * @param [in]  flags  フラグ。
 *
 * @retval 0以上 受信したデータの長さ(バイト単位)。ただし、0かつTCPならばデータ送信元がコネクションを閉じたことを示す。
 * @retval -1    エラーが起きた。
 * @retval -2    タイムアウトが起きた。
 */
ssize_t Socket::recv(void *buffer, size_t length, int flags)
{
  if (recv_timeout_ > 0) {
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(sock_, &fds);
    timeval tv;
    tv.tv_sec = recv_timeout_ / (1000 * 1000);
    tv.tv_usec = recv_timeout_ % (1000 * 1000);
    int n = select(sock_ + 1, &fds, NULL, NULL, &tv);
    if (n == 0 || !FD_ISSET(sock_, &fds)) {
      return -2;
    }
  }
  return ::recv(sock_, buffer, length, flags);
}

ssize_t Socket::recvfrom(void *buffer, size_t length, int flags, sockaddr *address, socklen_t *address_len)
{
  return ::recvfrom(sock_, buffer, length, flags, address, address_len);
}

/**
 * @brief データを送信する
 *
 * @param [in] buffer 送信データ。
 * @param [in] length bufferの長さ(バイト単位)。
 * @param [in] flags  フラグ。
 *
 * @retval 0以上 送信したデータの長さ(バイト単位)。
 * @retval -1    エラーが起きた。
 */
ssize_t Socket::send(const void *buffer, size_t length, int flags)
{
  return ::send(sock_, buffer, length, flags);
}

/**
 * @brief 送信先を指定してデータを送信する
 *
 * @param [in] buffer    送信データ。
 * @param [in] length    bufferの長さ(バイト単位)。
 * @param [in] flags     フラグ。
 * @param [in] dest_addr 送信先のアドレス。
 * @param [in] dest_len  dest_addrが示す構造体の大きさ(バイト単位)。
 *
 * @retval 0以上 送信したデータの長さ(バイト単位)。
 * @retval -1    エラーが起きた。
 */
ssize_t Socket::sendto(const void *buffer, size_t length, int flags, const sockaddr *dest_addr, socklen_t dest_len)
{
  return ::sendto(sock_, buffer, length, flags, dest_addr, dest_len);
}

/**
 * @brief オブジェクトの内容を文字列にして返す
 *
 * @return オブジェクトの内容を示す文字列。
 *
 * @code
 * Socket *sock = new Socket(PF_INET, SOCK_STREAM, 0);
 * sock->inspect(); // => "#<Socket:fd 3>"
 * @endcode
 */
std::string Socket::inspect() const
{
  char buf[128];
  snprintf(buf, sizeof buf, "#<Socket:fd %d>", sock_);
  std::string str(buf);
  return str;
}

/**
 * @brief ソケットに結び付けられているローカルアドレスをAddrinfoオブジェクトとして返す
 *
 * @retval NULL以外 ローカルアドレスを示すAddrinfoオブジェクトへのポインタ。
 * @retval NULL     ローカルアドレスを得られなかった。
 *
 * @code
 * Addrinfo *ai = Addrinfo::udp("127.0.0.1", 12345); // 自分のアドレス
 * Socket *sock = ai->bind();                        // アドレスを結び付けられたソケットが返る
 * Addrinfo *local = sock->local_address();          // ソケットから自分のアドレスを得る
 * @endcode
 */
Addrinfo *Socket::local_address() const
{
  sockaddr_in sin;
  socklen_t len = sizeof sin;
  int ret = getsockname(sock_, reinterpret_cast<sockaddr *>(&sin), &len);
  if (ret == -1) {
    perror("getsockname() failed");
    return NULL;
  }
  Addrinfo *ai = new Addrinfo(&sin);
  return ai;
}

/**
 * @brief ソケットの接続先のアドレスをAddrinfoオブジェクトとして返す
 *
 * @retval NULL以外 接続先アドレスを示すAddrinfoオブジェクトへのポインタ。
 * @retval NULL     接続先のアドレスを得られなかった。
 *
 * @code
 * Addrinfo *ai = Addrinfo::udp("127.0.0.1", 12345); // 通信相手のアドレス
 * Socket *sock = ai->connect();                     // 通信相手と接続したソケットが返る
 * Addrinfo *remote = sock->remote_address();        // ソケットから通信相手のアドレスを得る
 * @endcode
 */
Addrinfo *Socket::remote_address() const
{
  sockaddr_in sin;
  socklen_t len = sizeof sin;
  int ret = getpeername(sock_, reinterpret_cast<sockaddr *>(&sin), &len);
  if (ret == -1) {
    perror("getpeername() failed");
    return NULL;
  }
  Addrinfo *ai = new Addrinfo(&sin);
  return ai;
}

bool Socket::set_nonblocking_mode(const bool on_off)
{
  int value = fcntl(sock_, F_GETFL, 0);
  if (value <0) {
    perror("fcntl() failed");
    return false;
  }
  if (on_off) {
    value |= O_NONBLOCK;
  } else {
    value &= ~O_NONBLOCK;
  }
  if (fcntl(sock_, F_SETFL, value) == -1) {
    perror("fctl() failed");
    return false;
  }
  return true;
}

/**
 * @brief 受信処理のタイムアウト時間を設定する
 *
 * @param [in] usec タイムアウト時間(マイクロ秒単位)。
 */
void Socket::set_recv_timeout(const uint64_t usec)
{
  recv_timeout_ = usec;
}
