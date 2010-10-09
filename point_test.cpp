#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "point.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "vector.hpp"

class PointTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(PointTest);
  CPPUNIT_TEST(test_CTOR);
  CPPUNIT_TEST(test_ADDEQ);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_CTOR();
  void test_ADDEQ();
};

void PointTest::test_CTOR()
{
  Point p1;
  CPPUNIT_ASSERT_EQUAL(0.0f, p1.x);
  CPPUNIT_ASSERT_EQUAL(0.0f, p1.y);
  Point p2(1, 2);
  CPPUNIT_ASSERT_EQUAL(1.0f, p2.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, p2.y);
}

void PointTest::test_ADDEQ()
{
  Point p(1, 2);
  Vector v(3, 4);
  p += v;
  CPPUNIT_ASSERT_EQUAL(4.0f, p.x);
  CPPUNIT_ASSERT_EQUAL(6.0f, p.y);
}

CPPUNIT_TEST_SUITE_REGISTRATION(PointTest);
