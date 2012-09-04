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
