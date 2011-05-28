#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "rect.hpp"
#include <gtest/gtest.h>

TEST(RectTest, is_intersected)
{
  Rect r1(0, 0, 10, 10);
  EXPECT_TRUE(r1.is_intersected(Rect(  0,   0,  10,  10)));
  EXPECT_TRUE(r1.is_intersected(Rect(  1,   1,   5,   5)));
  EXPECT_TRUE(r1.is_intersected(Rect(  1,   1,  20,  20)));
  EXPECT_TRUE(r1.is_intersected(Rect( 10,   0,  10,  10)));
  EXPECT_TRUE(r1.is_intersected(Rect(-10,   0,  10,  10)));
  EXPECT_TRUE(r1.is_intersected(Rect(  0,  10,  10,  10)));
  EXPECT_TRUE(r1.is_intersected(Rect(  0, -10,  10,  10)));
  EXPECT_FALSE(r1.is_intersected(Rect( 11,   0,  10,  10)));
  EXPECT_FALSE(r1.is_intersected(Rect(-11,   0,  10,  10)));
  EXPECT_FALSE(r1.is_intersected(Rect(  0,  11,  10,  10)));
  EXPECT_FALSE(r1.is_intersected(Rect(  0, -11,  10,  10)));
}
