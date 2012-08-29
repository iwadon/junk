#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sound.hpp"
#include <gtest/gtest.h>

TEST(SoundTest, LoadSndFile)
{
  Sound snd;
  EXPECT_TRUE(snd.LoadSndFile("data/sound_data_sample.bin"));
  EXPECT_FALSE(snd.LoadSndFile("data/sample.mid"));
}
