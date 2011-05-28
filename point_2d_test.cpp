#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "point_2d.hpp"
#include <gtest/gtest.h>
#include "vector_2d.hpp"

TEST(Point2DTest, CTOR)
{
  Point2D p1;
  EXPECT_EQ(0.0f, p1.x);
  EXPECT_EQ(0.0f, p1.y);
  Point2D p2(1, 2);
  EXPECT_EQ(1.0f, p2.x);
  EXPECT_EQ(2.0f, p2.y);
}

TEST(Point2DTest, ADDEQ)
{
  Point2D p(1, 2);
  Vector2D v(3, 4);
  p += v;
  EXPECT_EQ(4.0f, p.x);
  EXPECT_EQ(6.0f, p.y);
}

TEST(Point2DTest, ADD)
{
  Point2D p1(1.0f, 2.0f);
  Vector2D v(3.0f, 4.0f);
  Point2D p2(4.0f, 6.0f);
  EXPECT_EQ(p2, p1 + v);
}

TEST(Point2DTest, SUB)
{
  Point2D p1(1.0f, 2.0f);
  Point2D p2(3.0f, 4.0f);
  Vector2D v(2.0f, 2.0f);
  EXPECT_EQ(v, p2 - p1);
}

TEST(Point2DTest, EQEQ)
{
  Point2D p1(1, 2);
  Point2D p2(1, 2);
  EXPECT_EQ(p2, p1);
}

TEST(Point2DTest, inspect)
{
  Point2D p(1.23f, 0.456f);
  EXPECT_EQ(std::string("(1.23, 0.46)"), p.inspect());
}

TEST(Point2DTest, rotate)
{
  Point2D p(1.0f, 0.0f);
  ASSERT_EQ(p, p.rotate(M_PI * 0.5f, Point2D(0.0f, 0.0f)));
  EXPECT_NEAR(0.0f, p.x, FLT_EPSILON);
  EXPECT_NEAR(1.0f, p.y, FLT_EPSILON);
}
