#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "circular_buffer.hpp"
#include <gtest/gtest.h>

namespace {
  float randf(float min, float max)
  {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (max - min));
  }
}

class CircularBufferTest : public ::testing::Test
{
protected:
  float values_[8];
  void SetUp();
};

void CircularBufferTest::SetUp()
{
  for (int i = 0; i < 8; ++i) {
    values_[i] = randf(-1.0f, 1.0f);
  }
}

TEST_F(CircularBufferTest, Read) {
  CircularBuffer<float, 8> cb;
  cb.Write(values_, 8);
  float read_values[8];
  EXPECT_EQ(8, cb.Read(read_values, 8));
  EXPECT_EQ(0, memcmp(read_values, values_, sizeof (float) * 8));
  cb.Write(values_, 5);
  EXPECT_EQ(3, cb.Read(read_values, 3));
  EXPECT_EQ(2, cb.Read(read_values, 3));
  EXPECT_EQ(0, cb.Read(read_values, 3));
}

TEST_F(CircularBufferTest, Write) {
  CircularBuffer<float, 8> cb;
  EXPECT_EQ(8, cb.Write(values_, 8));
  float values2[8];
  cb.Read(values2, 5);
  EXPECT_EQ(3, cb.Write(values_, 3));
  EXPECT_EQ(2, cb.Write(values_, 3));
  EXPECT_EQ(0, cb.Write(values_, 3));
}
