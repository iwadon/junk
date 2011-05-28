#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "smf.hpp"
#include <gtest/gtest.h>
#include <SDL.h>
#include "song.hpp"

class SmfTest : public ::testing::Test
{
protected:
  void *data_;

  void SetUp()
  {
    SDL_RWops *ctx = SDL_RWFromFile("data/sample.mid", "rb");
    ASSERT_TRUE(ctx != NULL);
    size_t len = SDL_RWseek(ctx, 0, RW_SEEK_END);
    SDL_RWseek(ctx, 0, RW_SEEK_SET);
    data_ = SDL_malloc(len);
    ASSERT_TRUE(data_ != NULL);
    int ret = SDL_RWread(ctx, data_, len, 1);
    ASSERT_EQ(1, ret);
    ret = SDL_RWclose(ctx);
    ASSERT_NE(-1, ret);
  }

  void TearDown()
  {
    SDL_free(data_);
    data_ = NULL;
  }
};

static std::string format(const char *format, ...)
{
  char buf[256];
  va_list args;
  va_start(args, format);
  vsnprintf(buf, sizeof buf, format, args);
  va_end(args);
  std::string result(buf);
  return result;
}

TEST_F(SmfTest, is_playing)
{
  Song song;
  SMF smf(song);
  EXPECT_EQ(false, smf.is_playing());
  smf.set_data(data_);
  EXPECT_EQ(false, smf.is_playing());
}

TEST_F(SmfTest, set_data)
{
  Song song;
  SMF smf(song);
  EXPECT_EQ(true, smf.set_data(data_));
}

#ifdef SMF_DEBUG

TEST_F(SmfTest, inspect)
{
  Song song;
  SMF smf(song);
  EXPECT_EQ(format("#<SMF:%p format 0, 0 track(s), timebase=48>", &smf), smf.inspect());
  smf.set_data(data_);
  EXPECT_EQ(format("#<SMF:%p format 1, 2 track(s), timebase=480>", &smf), smf.inspect());
}

#endif // defined(SMF_DEBUG)
