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
  CPPUNIT_TEST(test_activate);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_elapsed_time();
  void test_activate();
};

#define ASSERT_TIME(a, b) {						\
    static const double base = LoadTime::TIME_BASE_SEC;			\
    static const double base_ms = LoadTime::TIME_BASE_MILLISEC;		\
    CPPUNIT_ASSERT_DOUBLES_EQUAL(a, b / base, 1.0 / (base / base_ms)); \
  }

void LoadTimeTest::test_elapsed_time()
{
  LoadTime lt;
  lt.activate(0);
  lt.start(0);
  sleep(1);
  lt.stop(0);
  lt.flip();
  ASSERT_TIME(1.0, lt.elapsed_time(0));
}

void LoadTimeTest::test_activate()
{
  LoadTime lt;
  lt.start(0); sleep(1); lt.stop(0);
  lt.start(1); sleep(1); lt.stop(1);
  lt.flip();
  ASSERT_TIME(0.0, lt.elapsed_time(0));
  ASSERT_TIME(0.0, lt.elapsed_time(1));
  lt.activate(0);
  lt.start(0); sleep(1); lt.stop(0);
  lt.start(1); sleep(1); lt.stop(1);
  lt.flip();
  ASSERT_TIME(1.0, lt.elapsed_time(0));
  ASSERT_TIME(0.0, lt.elapsed_time(1));
  lt.activate(1);
  lt.start(0); sleep(1); lt.stop(0);
  lt.start(1); sleep(1); lt.stop(1);
  lt.flip();
  ASSERT_TIME(1.0, lt.elapsed_time(0));
  ASSERT_TIME(1.0, lt.elapsed_time(1));
}

CPPUNIT_TEST_SUITE_REGISTRATION(LoadTimeTest);
