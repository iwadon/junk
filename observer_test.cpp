#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "observer.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

static int n = 0;

class TestObserver : public Observer
{
public:
  void update(Subject */*subject*/)
  {
    ++n;
  }
};

class ObserverTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(ObserverTest);
  CPPUNIT_TEST(test_notify);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_notify();
};

void ObserverTest::test_notify()
{
  Subject s;
  TestObserver o;
  n = 0;
  s.notify();
  CPPUNIT_ASSERT_EQUAL(0, n);
  s.attach(&o);
  s.notify();
  CPPUNIT_ASSERT_EQUAL(1, n);
  s.detach(&o);
  s.notify();
  CPPUNIT_ASSERT_EQUAL(1, n);
}

CPPUNIT_TEST_SUITE_REGISTRATION(ObserverTest);
