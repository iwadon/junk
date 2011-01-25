#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "voice.hpp"
#include <cstdarg>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include "channel.hpp"
#include "instrument.hpp"

class VoiceTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(VoiceTest);
#ifdef VOICE_DEBUG
  CPPUNIT_TEST(test_inspect);
#endif
  CPPUNIT_TEST_SUITE_END();
public:
  void test_update();
  void test_play();
  void test_stop();
  void test_is_playing();
  void test_note();
#ifdef VOICE_DEBUG
  void test_inspect();
#endif
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

void VoiceTest::test_update()
{
}

void VoiceTest::test_play()
{
}

void VoiceTest::test_stop()
{
}

void VoiceTest::test_is_playing()
{
}

void VoiceTest::test_note()
{
}

#ifdef VOICE_DEBUG

void VoiceTest::test_inspect()
{
  Instrument i;
  Channel c(i, "ch");
  Voice v1(&c, 60, 64);
  CPPUNIT_ASSERT_EQUAL(format("#<Voice:%p     NONE  C4 64>", &v1), v1.inspect());
  Voice v2(&c, 61, 127);
  CPPUNIT_ASSERT_EQUAL(format("#<Voice:%p     NONE C#4 127>", &v2), v2.inspect());
}

#endif // defined(VOICE_DEBUG)

CPPUNIT_TEST_SUITE_REGISTRATION(VoiceTest);
