#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "line_segment_2d.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class LineSegment2DTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(LineSegment2DTest);
  CPPUNIT_TEST(test_cross_point);
  CPPUNIT_TEST(test_inspect);
  CPPUNIT_TEST(test_is_crossed);
  CPPUNIT_TEST(test_length);
  CPPUNIT_TEST(test_side);
  CPPUNIT_TEST(test_vector);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_cross_point();
  void test_inspect();
  void test_is_crossed();
  void test_length();
  void test_side();
  void test_vector();
};

void LineSegment2DTest::test_cross_point()
{
  LineSegment2D l1(0.0f, 0.0f, 1.0f, 1.0f);
  LineSegment2D l2(1.0f, 0.0f, 0.0f, 1.0f);
  Point2D cp1;
  Point2D cp2(0.5f, 0.5f);
  float t1, t2;
  CPPUNIT_ASSERT_EQUAL(true, l1.cross_point(l2, &cp1, &t1, &t2));
  CPPUNIT_ASSERT_EQUAL(cp2, cp1);
  CPPUNIT_ASSERT_EQUAL(0.5f, t1);
  CPPUNIT_ASSERT_EQUAL(0.5f, t2);
}

void LineSegment2DTest::test_inspect()
{
  LineSegment2D l1(1.23f, 0.456f, 7.8f, 9.012f);
  CPPUNIT_ASSERT_EQUAL(std::string("(1.23, 0.46)-(7.80, 9.01)"), l1.inspect());
}

void LineSegment2DTest::test_is_crossed()
{
  LineSegment2D l1(0.0f, 0.0f, 1.0f, 1.0f);
  LineSegment2D l2(1.0f, 0.0f, 0.0f, 1.0f);
  LineSegment2D l3(0.5f, 0.5f, 1.0f, 0.0f);
  LineSegment2D l4(2.0f, 3.0f, 4.0f, 5.0f);
  LineSegment2D l5(1.0f, 0.0f, 0.6f, 0.4f);
  LineSegment2D l6(2.0f, 1.0f, 1.0f, 2.0f);
  CPPUNIT_ASSERT_EQUAL(true,  l1.is_crossed(l2));
  CPPUNIT_ASSERT_EQUAL(true,  l1.is_crossed(l3));
  CPPUNIT_ASSERT_EQUAL(false, l1.is_crossed(l4));
  CPPUNIT_ASSERT_EQUAL(false, l1.is_crossed(l5));
  CPPUNIT_ASSERT_EQUAL(false, l1.is_crossed(l6));
}

void LineSegment2DTest::test_length()
{
  LineSegment2D l1(0, 0, 0, 0);
  CPPUNIT_ASSERT_EQUAL(0.0f, l1.length());
  LineSegment2D l2(0, 0, 1, 0);
  CPPUNIT_ASSERT_EQUAL(1.0f, l2.length());
}

void LineSegment2DTest::test_side()
{
  LineSegment2D l1(0.0f, 0.0f, 1.0f, 1.0f);
  Point2D p1(0.0f, 1.0f);
  CPPUNIT_ASSERT_EQUAL(-1.0f, l1.side(p1));
  Point2D p2(0.5f, 0.5f);
  CPPUNIT_ASSERT_EQUAL(0.0f, l1.side(p2));
  Point2D p3(1.0f, 0.0f);
  CPPUNIT_ASSERT_EQUAL(1.0f, l1.side(p3));
}

void LineSegment2DTest::test_vector()
{
  LineSegment2D l1(0, 0, 1, 1);
  Vector2D v1(1, 1);
  CPPUNIT_ASSERT_EQUAL(v1, l1.vector());
}

CPPUNIT_TEST_SUITE_REGISTRATION(LineSegment2DTest);
