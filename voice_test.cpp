#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "voice.hpp"
#include <gtest/gtest.h>
#include <cstdarg>
#include <string>
#include "channel.hpp"
#include "instrument.hpp"

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

#ifdef VOICE_DEBUG

TEST(VoiceTest, inspect)
{
  Instrument i;
  Channel c(i, "ch");
  Voice v1(&c, 60, 64);
  EXPECT_EQ(format("#<Voice:%p     NONE  C4 64>", &v1), v1.inspect());
  Voice v2(&c, 61, 127);
  ASSERT_EQ(format("#<Voice:%p     NONE C#4 127>", &v2), v2.inspect());
}

#endif // defined(VOICE_DEBUG)
