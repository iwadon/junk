#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "smf.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class SmfTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(SmfTest);
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

void SmfTest::test_is_playing()
{
  SMF smf;
  CPPUNIT_ASSERT_EQUAL(false, smf.is_playing());
  smf.load_file("data/sample.mid");
  CPPUNIT_ASSERT_EQUAL(false, smf.is_playing());
}

void SmfTest::test_load_file()
{
  SMF smf;
  CPPUNIT_ASSERT_EQUAL(true, smf.load_file("data/sample.mid"));
  CPPUNIT_ASSERT_EQUAL(false, smf.load_file("UNKNOWN FILE"));
}

void SmfTest::test_play()
{
}

void SmfTest::test_update()
{
}

CPPUNIT_TEST_SUITE_REGISTRATION(SmfTest);
