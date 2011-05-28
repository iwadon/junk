#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "circular_buffer.hpp"
#include <gtest/gtest.h>

TEST(CircularBufferTest, get)
{
  CircularBuffer<8> cb(8);
  EXPECT_EQ(0.0f, cb.get());
}

TEST(CircularBufferTest, set)
{
  CircularBuffer<4> cb(4);
  EXPECT_EQ(0.0f, cb.get());
  cb.set(1.0f);
  cb.next();
  EXPECT_EQ(0.0f, cb.get());
  cb.set(2.0f);
  cb.next();
  EXPECT_EQ(0.0f, cb.get());
  cb.set(3.0f);
  cb.next();
  EXPECT_EQ(0.0f, cb.get());
  cb.set(4.0f);
  cb.next();
  EXPECT_EQ(1.0f, cb.get());
  cb.set(5.0f);
  cb.next();
  EXPECT_EQ(2.0f, cb.get());
  cb.set(6.0f);
  cb.next();
  EXPECT_EQ(3.0f, cb.get());
  cb.set(7.0f);
  cb.next();
  EXPECT_EQ(4.0f, cb.get());
  cb.set(8.0f);
  cb.next();
  EXPECT_EQ(5.0f, cb.get());
  cb.next();
  EXPECT_EQ(6.0f, cb.get());
  cb.next();
  EXPECT_EQ(7.0f, cb.get());
  cb.next();
  EXPECT_EQ(8.0f, cb.get());
  cb.next();
}

TEST(CircularBufferTest, size)
{
  CircularBuffer<256> cb(8);
  EXPECT_EQ(static_cast<size_t>(8), cb.size());
}

TEST(CircularBufferTest, set_size)
{
  CircularBuffer<8> cb(8);
  cb.set_size(1);
  EXPECT_EQ(static_cast<size_t>(1), cb.size());
  cb.set_size(4);
  EXPECT_EQ(static_cast<size_t>(4), cb.size());
  cb.set_size(0);
  EXPECT_EQ(static_cast<size_t>(1), cb.size());
  cb.set_size(9);
  EXPECT_EQ(static_cast<size_t>(8), cb.size());
}

TEST(CircularBufferTest, capacity)
{
  CircularBuffer<256> cb(8);
  EXPECT_EQ(static_cast<size_t>(256), cb.capacity());
}
