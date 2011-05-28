#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator_stream.hpp"
#include <gtest/gtest.h>

TEST(OscillatorStreamTest, read)
{
  int16_t buf[10];
  OscillatorStream os1;
  size_t read_size = os1.read(buf, sizeof buf, 1.0f);
  EXPECT_EQ(static_cast<size_t>(sizeof buf), read_size);
  static const int16_t result1[] = {0, 32767, 0, -32767, 0, 32767, 0, -32767, 0, 32767};
  EXPECT_EQ(0, memcmp(buf, result1, 10));

  OscillatorStream os2;
  read_size = os2.read(buf, sizeof buf, 1.5f);
  EXPECT_EQ(static_cast<size_t>(sizeof buf), read_size);
  static const int16_t result2[] = {0, 23169, -32767, 23169, 0, -23169, 32767, -23169, 0, 23169};
  //static const int16_t result2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(result2[i], buf[i]);
  }

  OscillatorStream os3;
  read_size = os3.read(buf, sizeof buf, 0.5f);
  EXPECT_EQ(static_cast<size_t>(sizeof buf), read_size);
  static const int16_t result3[] = {0, 23169, 32767, 23169, 0, -23169, -32767, -23169, 0, 23169};
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(result3[i], buf[i]);
  }
}
