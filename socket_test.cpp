#include "socket.hpp"
#include "gtest/gtest.h"
#include <boost/shared_ptr.hpp>
#include <pthread.h>
#include <re2/re2.h>
#include <sys/socket.h>
#include "addrinfo.hpp"

TEST(SocketTest, get_sockaddr_in) {
  sockaddr_in sin;
  ASSERT_TRUE(Socket::get_sockaddr_in(sin, 80, "127.0.0.1"));
  EXPECT_EQ(sizeof (sockaddr_in), sin.sin_len);
  EXPECT_EQ(AF_INET, sin.sin_family);
  EXPECT_EQ(80, ntohs(sin.sin_port));
  EXPECT_TRUE(memcmp(&sin.sin_addr.s_addr, "\x7f\x00\x00\x01", 4) == 0);
}

TEST(SocketTest, get_sockaddr_in_2) {
  sockaddr_in sin;
  ASSERT_TRUE(Socket::get_sockaddr_in(sin, "http", "127.0.0.1"));
  EXPECT_EQ(sizeof (sockaddr_in), sin.sin_len);
  EXPECT_EQ(AF_INET, sin.sin_family);
  EXPECT_EQ(80, ntohs(sin.sin_port));
  EXPECT_TRUE(memcmp(&sin.sin_addr.s_addr, "\x7f\x00\x00\x01", 4) == 0);
}

TEST(SocketTest, get_sockaddr_in_3) {
  sockaddr_in sin;
  ASSERT_TRUE(Socket::get_sockaddr_in(sin, 80, "localhost"));
  EXPECT_EQ(sizeof (sockaddr_in), sin.sin_len);
  EXPECT_EQ(AF_INET, sin.sin_family);
  EXPECT_EQ(80, ntohs(sin.sin_port));
  EXPECT_TRUE(memcmp(&sin.sin_addr.s_addr, "\x7f\x00\x00\x01", 4) == 0);
}

TEST(SocketTest, get_sockaddr_in_4) {
  sockaddr_in sin;
  ASSERT_TRUE(Socket::get_sockaddr_in(sin, "http", "localhost"));
  EXPECT_EQ(sizeof (sockaddr_in), sin.sin_len);
  EXPECT_EQ(AF_INET, sin.sin_family);
  EXPECT_EQ(80, ntohs(sin.sin_port));
  EXPECT_TRUE(memcmp(&sin.sin_addr.s_addr, "\x7f\x00\x00\x01", 4) == 0);
}

TEST(SocketTest, tcp) {
  Socket *sock = Socket::tcp("moonrock.jp", "http");
  ASSERT_TRUE(sock != NULL);
  delete sock;
}

TEST(SocketTest, udp) {
  Socket *sock = Socket::udp();
  ASSERT_TRUE(sock != NULL);
  delete sock;
}

TEST(SocketTest, ctor) {
  Socket *sock = new Socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  ASSERT_TRUE(sock != NULL);
  delete sock;
}

TEST(SocketTest, connect) {
  Socket *sock = new Socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  sockaddr_in sin;
  socklen_t len = sizeof sin;
  Socket::get_sockaddr_in(sin, "http", "moonrock.jp");
  ASSERT_EQ(0, sock->connect(reinterpret_cast<sockaddr *>(&sin), len));
  delete sock;
}

#if 0

class RecvThread
{
public:
  RecvThread()
    : ready_(false)
  {
    pthread_mutex_init(&mutex_, NULL);
    pthread_cond_init(&cond_, NULL);
    ThreadArg ta = {this};
    pthread_create(&th_, NULL, th_entry, &ta);
  }
  ~RecvThread()
  {
    pthread_detach(th_);
    pthread_cond_destroy(&cond_);
    pthread_mutex_destroy(&mutex_);
  }
  static void *th_entry(void *arg)
  {
    return reinterpret_cast<ThreadArg *>(arg)->instance->th_main();
  }
  void *th_main()
  {
    boost::shared_ptr<Addrinfo> ai(Addrinfo::udp("localhost", "12345"));
    boost::shared_ptr<Socket> sock(ai->bind());
    socklen_t len = sizeof src_addr_;
    pthread_mutex_lock(&mutex_);
    ready_ = true;
    pthread_cond_broadcast(&cond_);
    pthread_mutex_unlock(&mutex_);
    recv_bytes_ = sock->recvfrom(buf_, sizeof buf_, 0, reinterpret_cast<sockaddr *>(&src_addr_), &len);
    return NULL;
  }
  void wait()
  {
    pthread_mutex_lock(&mutex_);
    while (!ready_) {
      pthread_cond_wait(&cond_, &mutex_);
    }
    pthread_mutex_unlock(&mutex_);
  }
  void join()
  {
    pthread_join(th_, NULL);
  }
  const char *buf() const { return buf_; }
  const sockaddr_in &src_addr() const { return src_addr_; }
  ssize_t recv_bytes() const { return recv_bytes_; }
private:
  struct ThreadArg { RecvThread *instance; };
  pthread_t th_;
  pthread_mutex_t mutex_;
  pthread_cond_t cond_;
  bool ready_;
  char buf_[10];
  sockaddr_in src_addr_;
  ssize_t recv_bytes_;
};

TEST(SocketTest, recvfrom) {
  RecvThread recv_th;
  boost::shared_ptr<Socket> sock(new Socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP));
  sockaddr_in sin;
  Socket::get_sockaddr_in(sin, 12345, "localhost");
  recv_th.wait();
  ssize_t sent_bytes = sock->sendto("HELLO", 5, 0, reinterpret_cast<sockaddr *>(&sin), sizeof sin);
  ASSERT_NE(-1, sent_bytes);
  recv_th.join();
  ASSERT_STREQ("HELLO", recv_th.buf());
  ASSERT_EQ(5, recv_th.recv_bytes());
  ASSERT_EQ(sin.sin_len, recv_th.src_addr().sin_len);
  ASSERT_EQ(sin.sin_family, recv_th.src_addr().sin_family);
  //ASSERT_EQ(sin.sin_port, recv_th.src_addr().sin_port);
  ASSERT_TRUE(memcmp(&recv_th.src_addr().sin_addr.s_addr, &sin.sin_addr.s_addr, 4) == 0);
}

#endif // 0

TEST(SocketTest, sendto) {
  boost::shared_ptr<Socket> sock(new Socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP));
  sockaddr_in sin;
  Socket::get_sockaddr_in(sin, "12345", "localhost");
  ssize_t sent_bytes = sock->sendto("HELLO", 5, 0, reinterpret_cast<sockaddr *>(&sin), sizeof sin);
  ASSERT_NE(-1, sent_bytes);
}

TEST(SocketTest, inspect) {
  Socket *sock = new Socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  EXPECT_TRUE(re2::RE2::FullMatch(sock->inspect(), "#<Socket:fd \\d+>"));
  delete sock;
}

TEST(SocketTest, operator_LSHIFT) {
  Socket sock(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  testing::internal::CaptureStdout();
  std::cout << sock;
  EXPECT_TRUE(re2::RE2::FullMatch(testing::internal::GetCapturedStdout().c_str(), "#<Socket:fd \\d+>"));
}

TEST(SocketTest, set_recv_timeout) {
  Socket *sock = Socket::udp();
  sock->set_recv_timeout(1);
  char buf[1];
  int ret = sock->recv(buf, sizeof buf, 0);
  ASSERT_EQ(-2, ret);
}

TEST(SocketTest, local_address) {
  boost::shared_ptr<Socket> sock(Socket::tcp("localhost", "http"));
  boost::shared_ptr<Addrinfo> ai(sock->local_address());
  ASSERT_EQ(0, memcmp(&ai->addr_in()->sin_addr, "\x7f\x00\x00\x01", 4)); // 127.0.0.1
}

TEST(SocketTest, remote_address) {
  boost::shared_ptr<Socket> sock(Socket::tcp("example.com", "http"));
  boost::shared_ptr<Addrinfo> ai(sock->remote_address());
  ASSERT_EQ(0, memcmp(&ai->addr_in()->sin_addr, "\xC0\x00+\n", 4)); // 192.0.43.10
}

TEST(SocketTest, set_nonblocking_mode) {
  boost::shared_ptr<Socket> sock(Socket::tcp("localhost", "http"));
  ASSERT_TRUE(sock->set_nonblocking_mode(true));
  ASSERT_TRUE(sock->set_nonblocking_mode(false));

  boost::shared_ptr<Socket> sock2(Socket::udp());
  ASSERT_TRUE(sock2->set_nonblocking_mode(true));
  ASSERT_TRUE(sock2->set_nonblocking_mode(false));
}
