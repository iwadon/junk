#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "channel.hpp"
#include <gtest/gtest.h>
#include <cstdarg>
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

TEST(ChannelTest, inspect)
{
  Instrument inst;
  Channel c1(inst, "ch01");
  EXPECT_EQ(format("#<Channel:%p ch01>", &c1), c1.inspect());
  c1.note_on(60, 64);
  EXPECT_EQ(format("#<Channel:%p ch01>", &c1), c1.inspect());
  c1.note_on(64, 64);
  EXPECT_EQ(format("#<Channel:%p ch01>", &c1), c1.inspect());
}
