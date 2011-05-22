#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "point_2d.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "vector_2d.hpp"

class Point2DTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(Point2DTest);
  CPPUNIT_TEST(test_CTOR);
  CPPUNIT_TEST(test_ADDEQ);
  CPPUNIT_TEST(test_ADD);
  CPPUNIT_TEST(test_SUB);
  CPPUNIT_TEST(test_EQEQ);
  CPPUNIT_TEST(test_inspect);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_CTOR();
  void test_ADDEQ();
  void test_ADD();
  void test_SUB();
  void test_EQEQ();
  void test_inspect();
};

void Point2DTest::test_CTOR()
{
  Point2D p1;
  CPPUNIT_ASSERT_EQUAL(0.0f, p1.x);
  CPPUNIT_ASSERT_EQUAL(0.0f, p1.y);
  Point2D p2(1, 2);
  CPPUNIT_ASSERT_EQUAL(1.0f, p2.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, p2.y);
}

void Point2DTest::test_ADDEQ()
{
  Point2D p(1, 2);
  Vector2D v(3, 4);
  p += v;
  CPPUNIT_ASSERT_EQUAL(4.0f, p.x);
  CPPUNIT_ASSERT_EQUAL(6.0f, p.y);
}

void Point2DTest::test_ADD()
{
  Point2D p1(1.0f, 2.0f);
  Vector2D v(3.0f, 4.0f);
  Point2D p2(4.0f, 6.0f);
  CPPUNIT_ASSERT_EQUAL(p2, p1 + v);
}

void Point2DTest::test_SUB()
{
  Point2D p1(1.0f, 2.0f);
  Point2D p2(3.0f, 4.0f);
  Vector2D v(2.0f, 2.0f);
  CPPUNIT_ASSERT_EQUAL(v, p2 - p1);
}

void Point2DTest::test_EQEQ()
{
  Point2D p1(1, 2);
  Point2D p2(1, 2);
  CPPUNIT_ASSERT_EQUAL(p2, p1);
}

void Point2DTest::test_inspect()
{
  Point2D p(1.23f, 0.456f);
  CPPUNIT_ASSERT_EQUAL(std::string("(1.23, 0.46)"), p.inspect());
}

CPPUNIT_TEST_SUITE_REGISTRATION(Point2DTest);
