#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "song.hpp"
#include <gtest/gtest.h>

TEST(SongTest, is_playing)
{
  Song song;
  EXPECT_EQ(false, song.is_playing());
  song.load_file("data/sample.mid");
  EXPECT_EQ(false, song.is_playing());
}

TEST(SongTest, load_file)
{
  Song song;
  EXPECT_EQ(true, song.load_file("data/sample.mid"));
  EXPECT_EQ(false, song.load_file("UNKNOWN FILE"));
}
