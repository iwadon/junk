#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sound.hpp"
#include <gtest/gtest.h>

TEST(SoundTest, load_file)
{
  Sound snd;
  EXPECT_EQ(true, snd.load_file("data/sound_data_sample.bin"));
  EXPECT_EQ(false, snd.load_file("data/sample.mid"));
}
