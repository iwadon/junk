#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "point.hpp"
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
  CPPUNIT_ASSERT_EQUAL(0.0f, p1.x_);
  CPPUNIT_ASSERT_EQUAL(0.0f, p1.y_);
  Point p2(1, 2);
  CPPUNIT_ASSERT_EQUAL(1.0f, p2.x_);
  CPPUNIT_ASSERT_EQUAL(2.0f, p2.y_);
}

void PointTest::test_ADDEQ()
{
  Point p(1, 2);
  Vector v(3, 4);
  p += v;
  CPPUNIT_ASSERT_EQUAL(4.0f, p.x_);
  CPPUNIT_ASSERT_EQUAL(6.0f, p.y_);
}

CPPUNIT_TEST_SUITE_REGISTRATION(PointTest);
