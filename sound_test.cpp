#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sound.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class SoundTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(SoundTest);
  CPPUNIT_TEST(test_load_file);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_load_file();
};

void SoundTest::test_load_file()
{
  Sound snd;
  CPPUNIT_ASSERT_EQUAL(true, snd.load_file("data/sound_data_sample.bin"));
  CPPUNIT_ASSERT_EQUAL(false, snd.load_file("data/sample.mid"));
}

CPPUNIT_TEST_SUITE_REGISTRATION(SoundTest);
