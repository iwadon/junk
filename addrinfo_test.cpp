#include "addrinfo.hpp"
#include "socket.hpp"
#include "gtest/gtest.h"
#include <arpa/inet.h>
#include <iostream>
#include <shared_ptr.hpp>
#include <sys/socket.h>

TEST(AddrinfoTest, getaddrinfo) {
  std::vector<Addrinfo *> v = Addrinfo::getaddrinfo("moonrock.jp", "http");
  for (std::vector<Addrinfo *>::iterator i = v.begin(); i != v.end(); ++i) {
    Addrinfo *ai = *i;
    int sock = socket(ai->pfamily(), ai->socktype(), ai->protocol());
    ASSERT_NE(-1, sock);
    ASSERT_EQ(80, ntohs(ai->addr_in()->sin_port));
    ASSERT_EQ(0, connect(sock, ai->addr(), ai->addrlen()));
    ASSERT_EQ(0, close(sock));
    delete ai;
  }
}

TEST(AddrinfoTest, getaddrinfo2) {
  std::vector<Addrinfo *> v = Addrinfo::getaddrinfo("moonrock.jp", 80);
  for (std::vector<Addrinfo *>::iterator i = v.begin(); i != v.end(); ++i) {
    Addrinfo *ai = *i;
    int sock = socket(ai->pfamily(), ai->socktype(), ai->protocol());
    ASSERT_NE(-1, sock);
    ASSERT_EQ(80, ntohs(ai->addr_in()->sin_port));
    ASSERT_EQ(0, connect(sock, ai->addr(), ai->addrlen()));
    ASSERT_EQ(0, close(sock));
    delete ai;
  }
}

TEST(AddrinfoTest, tcp) {
  boost::shared_ptr<Addrinfo> ai(Addrinfo::tcp("localhost", "http"));
  ASSERT_TRUE(ai != NULL);
  EXPECT_EQ(0, ai->flags());
  EXPECT_EQ(PF_INET, ai->pfamily());
  EXPECT_EQ(SOCK_STREAM, ai->socktype());
  EXPECT_EQ(IPPROTO_TCP, ai->protocol());
  EXPECT_EQ(sizeof (sockaddr_in), ai->addrlen());
  EXPECT_EQ(AF_INET, ai->addr_in()->sin_family);
  EXPECT_EQ(80, ntohs(ai->addr_in()->sin_port));
  EXPECT_EQ(0, memcmp(&ai->addr_in()->sin_addr, "\x7f\x00\x00\x01", 4));
}

TEST(AddrinfoTest, tcp_2) {
  boost::shared_ptr<Addrinfo> ai(Addrinfo::tcp("localhost", 80));
  ASSERT_TRUE(ai != NULL);
  EXPECT_EQ(0, ai->flags());
  EXPECT_EQ(PF_INET, ai->pfamily());
  EXPECT_EQ(SOCK_STREAM, ai->socktype());
  EXPECT_EQ(IPPROTO_TCP, ai->protocol());
  EXPECT_EQ(sizeof (sockaddr_in), ai->addrlen());
  EXPECT_EQ(AF_INET, ai->addr_in()->sin_family);
  EXPECT_EQ(80, ntohs(ai->addr_in()->sin_port));
  EXPECT_EQ(0, memcmp(&ai->addr_in()->sin_addr, "\x7f\x00\x00\x01", 4));
}

TEST(AddrinfoTest, udp) {
  boost::shared_ptr<Addrinfo> ai(Addrinfo::udp("localhost", "http"));
  ASSERT_TRUE(ai != NULL);
  EXPECT_EQ(0, ai->flags());
  EXPECT_EQ(PF_INET, ai->pfamily());
  EXPECT_EQ(SOCK_DGRAM, ai->socktype());
  EXPECT_EQ(IPPROTO_UDP, ai->protocol());
  EXPECT_EQ(sizeof (sockaddr_in), ai->addrlen());
  EXPECT_EQ(AF_INET, ai->addr_in()->sin_family);
  EXPECT_EQ(80, ntohs(ai->addr_in()->sin_port));
  EXPECT_EQ(0, memcmp(&ai->addr_in()->sin_addr, "\x7f\x00\x00\x01", 4));
}

TEST(AddrinfoTest, udp_2) {
  boost::shared_ptr<Addrinfo> ai(Addrinfo::udp("localhost", 80));
  ASSERT_TRUE(ai != NULL);
  EXPECT_EQ(0, ai->flags());
  EXPECT_EQ(PF_INET, ai->pfamily());
  EXPECT_EQ(SOCK_DGRAM, ai->socktype());
  EXPECT_EQ(IPPROTO_UDP, ai->protocol());
  EXPECT_EQ(sizeof (sockaddr_in), ai->addrlen());
  EXPECT_EQ(AF_INET, ai->addr_in()->sin_family);
  EXPECT_EQ(80, ntohs(ai->addr_in()->sin_port));
  EXPECT_EQ(0, memcmp(&ai->addr_in()->sin_addr, "\x7f\x00\x00\x01", 4));
}

TEST(AddrinfoTest, ctor) {
  sockaddr_in sin;
  ASSERT_TRUE(Socket::get_sockaddr_in(sin, "http", "localhost"));
  Addrinfo ai(&sin);
  EXPECT_EQ(0, ai.flags());
  EXPECT_EQ(PF_INET, ai.pfamily());
  EXPECT_EQ(0, ai.socktype());
  EXPECT_EQ(0, ai.protocol());
  EXPECT_EQ(sizeof (sockaddr_in), ai.addrlen());
  EXPECT_EQ(AF_INET, ai.addr_in()->sin_family);
  EXPECT_EQ(80, ntohs(ai.addr_in()->sin_port));
  EXPECT_EQ(0, memcmp(&ai.addr_in()->sin_addr, "\x7f\x00\x00\x01", 4));
}

TEST(AddrinfoTest, bind) {
  boost::shared_ptr<Addrinfo> ai(Addrinfo::udp("localhost", 7777));
  ASSERT_TRUE(ai != NULL);
  Socket *sock = ai->bind();
  ASSERT_TRUE(sock != NULL);
  delete sock;
}

TEST(AddrinfoTest, inspect) {
  sockaddr_in sin1;
  ASSERT_TRUE(Socket::get_sockaddr_in(sin1, 80, "127.0.0.1"));
  Addrinfo ai1(&sin1);
  EXPECT_EQ("#<Addrinfo: 127.0.0.1:80>", ai1.inspect());

  boost::shared_ptr<Addrinfo> ai2(Addrinfo::tcp("127.0.0.1", 80));
  EXPECT_EQ("#<Addrinfo: 127.0.0.1:80 TCP>", ai2->inspect());

  boost::shared_ptr<Addrinfo> ai3(Addrinfo::udp("127.0.0.1", 80));
  EXPECT_EQ("#<Addrinfo: 127.0.0.1:80 UDP>", ai3->inspect());

  sockaddr_in sin4;
  ASSERT_TRUE(Socket::get_sockaddr_in(sin4, 0, ""));
  Addrinfo ai4(&sin4);
  EXPECT_EQ("#<Addrinfo: 0.0.0.0>", ai4.inspect());

  sockaddr_in sin5;
  ASSERT_TRUE(Socket::get_sockaddr_in(sin5, 1, ""));
  Addrinfo ai5(&sin5);
  EXPECT_EQ("#<Addrinfo: 0.0.0.0:1>", ai5.inspect());

  sockaddr_in sin6;
  ASSERT_TRUE(Socket::get_sockaddr_in(sin6, "", ""));
  Addrinfo ai6(&sin6);
  EXPECT_EQ("#<Addrinfo: 0.0.0.0>", ai6.inspect());
}

TEST(AddrinfoTest, operator_LSHIFT) {
    sockaddr_in sin;
    Socket::get_sockaddr_in(sin, 80, "127.0.0.1");
    Addrinfo ai(&sin);
    testing::internal::CaptureStdout();
    std::cout << ai;
    EXPECT_STREQ("#<Addrinfo: 127.0.0.1:80>", testing::internal::GetCapturedStdout().c_str());
}
