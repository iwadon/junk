#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "channel.hpp"
#include <cstdarg>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "instrument.hpp"

class ChannelTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(ChannelTest);
  CPPUNIT_TEST(test_inspect);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_inspect();
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

void ChannelTest::test_inspect()
{
  Instrument inst;
  Channel c1(inst, "ch01");
  CPPUNIT_ASSERT_EQUAL(format("#<Channel:%p ch01>", &c1), c1.inspect());
  c1.note_on(60, 64);
  CPPUNIT_ASSERT_EQUAL(format("#<Channel:%p ch01>", &c1), c1.inspect());
  c1.note_on(64, 64);
  CPPUNIT_ASSERT_EQUAL(format("#<Channel:%p ch01>", &c1), c1.inspect());
}

CPPUNIT_TEST_SUITE_REGISTRATION(ChannelTest);
