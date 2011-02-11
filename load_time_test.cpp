#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "load_time.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class LoadTimeTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(LoadTimeTest);
  CPPUNIT_TEST(test_elapsed_time);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_elapsed_time();
};

void LoadTimeTest::test_elapsed_time()
{
  LoadTime lt;
  lt.start(0);
  sleep(1);
  lt.stop(0);
  lt.flip();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1000 * LoadTime::TIME_BASE_MILLISEC, lt.elapsed_time(0), LoadTime::TIME_BASE_MILLISEC);
}

CPPUNIT_TEST_SUITE_REGISTRATION(LoadTimeTest);
