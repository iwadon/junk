#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "wav.hpp"
#include <gtest/gtest.h>

TEST(WavTest, LoadFile) {
  Wav wav;
  ASSERT_TRUE(wav.LoadFile("data/sin440.wav"));
  ASSERT_FALSE(wav.LoadFile("data/sample.mid"));
}

TEST(WavTest, ReadSamples) {
  Wav wav;
  wav.LoadFile("data/sin440.wav");
  int16_t buf[10000];
  ASSERT_EQ(10000, wav.ReadSamples(buf, 10000));
  ASSERT_EQ(10000, wav.ReadSamples(buf, 10000));
  ASSERT_EQ(10000, wav.ReadSamples(buf, 10000));
  ASSERT_EQ(10000, wav.ReadSamples(buf, 10000));
  ASSERT_EQ( 8000, wav.ReadSamples(buf, 10000));
  ASSERT_EQ(    0, wav.ReadSamples(buf, 10000));
}
