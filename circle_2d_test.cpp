#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "circle_2d.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class Circle2DTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(Circle2DTest);
  CPPUNIT_TEST(test_CTOR);
  CPPUNIT_TEST(test_is_include);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_CTOR();
  void test_is_include();
};

void Circle2DTest::test_CTOR()
{
  Circle2D c1;
  CPPUNIT_ASSERT_EQUAL(0.0f, c1.center.x);
  CPPUNIT_ASSERT_EQUAL(0.0f, c1.center.y);
  CPPUNIT_ASSERT_EQUAL(0.0f, c1.radius);
  Circle2D c2(1, 2, 3);
  CPPUNIT_ASSERT_EQUAL(1.0f, c2.center.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, c2.center.y);
  CPPUNIT_ASSERT_EQUAL(3.0f, c2.radius);
  Point2D c3p(1, 2);
  Circle2D c3(c3p, 3);
  CPPUNIT_ASSERT_EQUAL(1.0f, c3.center.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, c3.center.y);
  CPPUNIT_ASSERT_EQUAL(3.0f, c3.radius);
}

void Circle2DTest::test_is_include()
{
  Circle2D c(0, 0, 10);
  Point2D p1(0, 0);
  CPPUNIT_ASSERT(c.is_include(p1));
  Point2D p2(0, 10);
  CPPUNIT_ASSERT(c.is_include(p2));
  Point2D p3(0, 20);
  CPPUNIT_ASSERT(!c.is_include(p3));
}

CPPUNIT_TEST_SUITE_REGISTRATION(Circle2DTest);
