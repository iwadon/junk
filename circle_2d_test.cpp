#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "circle_2d.hpp"
#include <gtest/gtest.h>

TEST(Circle2DTest, CTOR)
{
  Circle2D c1;
  EXPECT_EQ(0.0f, c1.center.x);
  EXPECT_EQ(0.0f, c1.center.y);
  EXPECT_EQ(0.0f, c1.radius);
  Circle2D c2(1, 2, 3);
  EXPECT_EQ(1.0f, c2.center.x);
  EXPECT_EQ(2.0f, c2.center.y);
  EXPECT_EQ(3.0f, c2.radius);
  Point2D c3p(1, 2);
  Circle2D c3(c3p, 3);
  EXPECT_EQ(1.0f, c3.center.x);
  EXPECT_EQ(2.0f, c3.center.y);
  EXPECT_EQ(3.0f, c3.radius);
}

TEST(Circle2DTest, is_include)
{
  Circle2D c(0, 0, 10);
  Point2D p1(0, 0);
  EXPECT_TRUE(c.is_include(p1));
  Point2D p2(0, 10);
  EXPECT_TRUE(c.is_include(p2));
  Point2D p3(0, 20);
  EXPECT_TRUE(!c.is_include(p3));
}
