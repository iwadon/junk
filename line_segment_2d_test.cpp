#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "line_segment_2d.hpp"
#include <gtest/gtest.h>

TEST(LineSegment2DTest, CTOR)
{
  LineSegment2D l1(1.0f, 2.0f, 3.0f, 4.0f);
  EXPECT_EQ(1.0f, l1.p1.x);
  EXPECT_EQ(2.0f, l1.p1.y);
  EXPECT_EQ(3.0f, l1.p2.x);
  EXPECT_EQ(4.0f, l1.p2.y);

  Point2D p1(1.0f, 2.0f);
  Point2D p2(3.0f, 4.0f);
  LineSegment2D l2(p1, p2);
  EXPECT_EQ(1.0f, l2.p1.x);
  EXPECT_EQ(2.0f, l2.p1.y);
  EXPECT_EQ(3.0f, l2.p2.x);
  EXPECT_EQ(4.0f, l2.p2.y);
}

TEST(LineSegment2DTest, bound)
{
  {
    LineSegment2D l1(0.0f, 1.0f, 1.0f, 1.0f);
    LineSegment2D l2(0.0f, 0.0f, 0.8f, 1.5f);
    std::vector<Point2D> pa1;
    EXPECT_TRUE(l2.bound(pa1, l1));
    EXPECT_EQ(static_cast<size_t>(3), pa1.size());
  }
  {
    LineSegment2D l1(1.0f, 0.0f, 1.0f, 1.0f);
    LineSegment2D l2(0.0f, 0.0f, 1.5f, 0.8f);
    std::vector<Point2D> pa1;
    EXPECT_TRUE(l2.bound(pa1, l1));
    EXPECT_EQ(static_cast<size_t>(3), pa1.size());
  }
  {
    LineSegment2D l1(0.0f, 2.0f, 2.0f, 0.0f);
    LineSegment2D l2(1.0f, 0.0f, 1.0f, 2.0f);
    std::vector<Point2D> pa1;
    EXPECT_TRUE(l2.bound(pa1, l1));
    EXPECT_EQ(static_cast<size_t>(3), pa1.size());
    EXPECT_EQ(l2.p1, pa1[0]);
    EXPECT_NEAR(0.0f, pa1[2].x, FLT_EPSILON);
    EXPECT_NEAR(1.0f, pa1[2].y, FLT_EPSILON);
  }
}

TEST(LineSegment2DTest, cross_point)
{
  LineSegment2D l1(0.0f, 0.0f, 1.0f, 1.0f);
  LineSegment2D l2(1.0f, 0.0f, 0.0f, 1.0f);
  Point2D cp1;
  Point2D cp2(0.5f, 0.5f);
  float t1, t2;
  EXPECT_TRUE(l1.cross_point(l2, &cp1, &t1, &t2));
  EXPECT_EQ(cp2, cp1);
  EXPECT_EQ(0.5f, t1);
  EXPECT_EQ(0.5f, t2);
}

TEST(LineSegment2DTest, inspect)
{
  LineSegment2D l1(1.23f, 0.456f, 7.8f, 9.012f);
  EXPECT_EQ(std::string("(1.23, 0.46)-(7.80, 9.01)"), l1.inspect());
}

TEST(LineSegment2DTest, intersection_point)
{
#if 0
  LineSegment2D l1(1.0f, 0.0f, 0.0f, 1.0f);
  LineSegment2D l2(0.0f, 0.0f, 1.0f, 1.0f);
  Point2D p;
  EXPECT_TRUE(l1.intersection_point_with(p, l2));
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5f, p.x, 0.01f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5f, p.y, 0.01f);

  LineSegment2D l3(0.0f, 1.0f, 1.0f, 0.0f);
  EXPECT_TRUE(l3.intersection_point_with(p, l2));
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5f, p.x, 0.01f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5f, p.y, 0.01f);

  LineSegment2D l4(1.0f, 1.0f, 0.0f, 0.0f);
  EXPECT_TRUE(l3.intersection_point_with(p, l4));
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5f, p.x, 0.01f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5f, p.y, 0.01f);
#else
  LineSegment2D l1(0.0f, 0.0f, 1.0f, 1.0f);
  LineSegment2D l2(1.0f, 0.0f, 0.0f, 1.0f);
  Point2D cp1;
  Point2D cp2(0.5f, 0.5f);
  EXPECT_TRUE(l1.intersection_point_with(cp1, l2));
  EXPECT_EQ(cp2, cp1);
#endif
}

TEST(LineSegment2DTest, is_crossed)
{
  LineSegment2D l1(0.0f, 0.0f, 1.0f, 1.0f);
  LineSegment2D l2(1.0f, 0.0f, 0.0f, 1.0f);
  LineSegment2D l3(0.5f, 0.5f, 1.0f, 0.0f);
  LineSegment2D l4(2.0f, 3.0f, 4.0f, 5.0f);
  LineSegment2D l5(1.0f, 0.0f, 0.6f, 0.4f);
  LineSegment2D l6(2.0f, 1.0f, 1.0f, 2.0f);
  EXPECT_TRUE( l1.is_crossed(l2));
  EXPECT_TRUE( l1.is_crossed(l3));
  EXPECT_TRUE(!l1.is_crossed(l4));
  EXPECT_TRUE(!l1.is_crossed(l5));
  EXPECT_TRUE(!l1.is_crossed(l6));
}

TEST(LineSegment2DTest, length)
{
  LineSegment2D l1(0, 0, 0, 0);
  EXPECT_EQ(0.0f, l1.length());
  LineSegment2D l2(0, 0, 1, 0);
  EXPECT_EQ(1.0f, l2.length());
}

TEST(LineSegment2DTest, side)
{
  LineSegment2D l1(0.0f, 0.0f, 1.0f, 1.0f);
  Point2D p1(0.0f, 1.0f);
  EXPECT_EQ(-1.0f, l1.side(p1));
  Point2D p2(0.5f, 0.5f);
  EXPECT_EQ(0.0f, l1.side(p2));
  Point2D p3(1.0f, 0.0f);
  EXPECT_EQ(1.0f, l1.side(p3));
}

TEST(LineSegment2DTest, vector)
{
  LineSegment2D l1(0, 0, 1, 1);
  Vector2D v1(1, 1);
  EXPECT_EQ(v1, l1.vector());
}
