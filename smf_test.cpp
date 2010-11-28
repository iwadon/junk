#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "smf.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class SmfTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(SmfTest);
  CPPUNIT_TEST(test_load_file);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_load_file();
};

void SmfTest::test_load_file()
{
  SMF smf;
  CPPUNIT_ASSERT_EQUAL(true, smf.load_file("data/sample.mid"));
  CPPUNIT_ASSERT_EQUAL(false, smf.load_file("UNKNOWN FILE"));
}

CPPUNIT_TEST_SUITE_REGISTRATION(SmfTest);
