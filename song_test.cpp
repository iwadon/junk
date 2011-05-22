#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "song.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "sp.hpp"

class SongTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(SongTest);
  CPPUNIT_TEST(test_is_playing);
  CPPUNIT_TEST(test_load_file);
  CPPUNIT_TEST(test_play);
  CPPUNIT_TEST(test_update);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_is_playing();
  void test_load_file();
  void test_play();
  void test_update();
};

void SongTest::test_is_playing()
{
  Song song;
  CPPUNIT_ASSERT_EQUAL(false, song.is_playing());
  song.load_file("data/sample.mid");
  CPPUNIT_ASSERT_EQUAL(false, song.is_playing());
}

void SongTest::test_load_file()
{
  Song song;
  CPPUNIT_ASSERT_EQUAL(true, song.load_file("data/sample.mid"));
  CPPUNIT_ASSERT_EQUAL(false, song.load_file("UNKNOWN FILE"));
}

void SongTest::test_play()
{
}

void SongTest::test_update()
{
}

CPPUNIT_TEST_SUITE_REGISTRATION(SongTest);
