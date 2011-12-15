#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "vector_2d.hpp"
#include <gtest/gtest.h>
#include "point_2d.hpp"

TEST(Vector2DTest, CTOR)
{
  Vector2D v1;
  EXPECT_EQ(0.0f, v1.x);
  EXPECT_EQ(0.0f, v1.y);
  Vector2D v2(1, 2);
  EXPECT_EQ(1.0f, v2.x);
  EXPECT_EQ(2.0f, v2.y);
  Point2D p1(1, 2);
  Point2D p2(3, 4);
  Vector2D v4(p1, p2);
  EXPECT_FLOAT_EQ(2.0f, v4.x);
  EXPECT_FLOAT_EQ(2.0f, v4.y);
}

TEST(Vector2DTest, float)
{
  Vector2D v1(1.23f, 4.56f);
  float *f1 = v1;
  EXPECT_EQ(1.23f, f1[0]);
  EXPECT_EQ(4.56f, f1[1]);
}

TEST(Vector2DTest, const_float)
{
  Vector2D v1(1.23f, 4.56f);
  const float *f1 = v1;
  EXPECT_EQ(1.23f, f1[0]);
  EXPECT_EQ(4.56f, f1[1]);
}

TEST(Vector2DTest, ADDEQ)
{
  Vector2D v1(1, 2);
  Vector2D v2(3, 4);
  v1 += v2;
  EXPECT_EQ(4.0f, v1.x);
  EXPECT_EQ(6.0f, v1.y);
}

TEST(Vector2DTest, SUBEQ)
{
  Vector2D v1(1, 2);
  Vector2D v2(3, 4);
  v1 -= v2;
  EXPECT_EQ(-2.0f, v1.x);
  EXPECT_EQ(-2.0f, v1.y);
}

TEST(Vector2DTest, MULEQ)
{
  Vector2D v1(1, 2);
  v1 *= 2.5f;
  EXPECT_EQ(2.5f, v1.x);
  EXPECT_EQ(5.0f, v1.y);
  Vector2D v2(2, 1);
  v1 *= v2;
  EXPECT_EQ(5.0f, v1.x);
  EXPECT_EQ(5.0f, v1.y);
}

TEST(Vector2DTest, DIVEQ)
{
  Vector2D v1(1, 2);
  v1 /= 2.5f;
  EXPECT_EQ(0.4f, v1.x);
  EXPECT_EQ(0.8f, v1.y);
  Vector2D v2(2, 1);
  v1 /= v2;
  EXPECT_EQ(0.2f, v1.x);
  EXPECT_EQ(0.8f, v1.y);
}

TEST(Vector2DTest, PLUS)
{
  Vector2D v1(1.0f, 2.0f);
  EXPECT_EQ(v1, +v1);
}

TEST(Vector2DTest, MINUS)
{
  Vector2D v1( 1.0f,  2.0f);
  Vector2D v2(-1.0f, -2.0f);
  EXPECT_EQ(v2, -v1);
}

TEST(Vector2DTest, ADD)
{
  Vector2D v1(1, 2);
  Vector2D v2(3, 4);
  Vector2D v3 = v1 + v2;
  EXPECT_EQ(4.0f, v3.x);
  EXPECT_EQ(6.0f, v3.y);
}

TEST(Vector2DTest, SUB)
{
  Vector2D v1(1, 2);
  Vector2D v2(3, 4);
  Vector2D v3 = v1 - v2;
  EXPECT_EQ(-2.0f, v3.x);
  EXPECT_EQ(-2.0f, v3.y);
}

TEST(Vector2DTest, MUL)
{
  Vector2D v1(1, 2);
  Vector2D v2 = v1 * 2.5f;
  EXPECT_EQ(2.5f, v2.x);
  EXPECT_EQ(5.0f, v2.y);
  Vector2D v3(2, 1);
  Vector2D v4(1, 2);
  Vector2D v5 = v3 * v4;
  EXPECT_EQ(2.0f, v5.x);
  EXPECT_EQ(2.0f, v5.y);
}

TEST(Vector2DTest, DIV)
{
  Vector2D v1(1, 2);
  Vector2D v2 = v1 / 2.5f;
  EXPECT_EQ(0.4f, v2.x);
  EXPECT_EQ(0.8f, v2.y);
  Vector2D v3(2, 1);
  Vector2D v4(1, 2);
  Vector2D v5 = v3 / v4;
  EXPECT_EQ(2.0f, v5.x);
  EXPECT_EQ(0.5f, v5.y);
}

TEST(Vector2DTest, EQEQ)
{
  Vector2D v1(1, 2);
  Vector2D v2(1, 2);
  EXPECT_TRUE(v1 == v2);
  EXPECT_EQ(v2, v1);
}

TEST(Vector2DTest, NOTEQ)
{
  Vector2D v1(1, 2);
  Vector2D v2(2, 3);
  EXPECT_TRUE(v1 != v2);
}

TEST(Vector2DTest, angle_length)
{
  Vector2D v1 = Vector2D::angle_length(0.0f, 1.0f);
  EXPECT_FLOAT_EQ(1.0f, v1.x);
  EXPECT_FLOAT_EQ(0.0f, v1.y);
  v1 = Vector2D::angle_length(M_PI * 0.25f, 1.41421356f);
  EXPECT_FLOAT_EQ(1.0f, v1.x);
  EXPECT_FLOAT_EQ(1.0f, v1.y);
  v1 = Vector2D::angle_length(M_PI * 0.5f, 1.f);
  //EXPECT_FLOAT_EQ(0.0f, v1.x);
  EXPECT_NEAR(0.0f, v1.x, FLT_EPSILON);
  //EXPECT_FLOAT_EQ(1.0f, v1.y);
  EXPECT_NEAR(1.0f, v1.y, FLT_EPSILON);
}

TEST(Vector2DTest, cross)
{
  Vector2D v1(1.0f,  1.0f);
  Vector2D v2(1.0f, -1.0f);
  EXPECT_FLOAT_EQ(-2.0f, v1.cross(v2));
}

TEST(Vector2DTest, dot)
{
  Vector2D v1(1.0f,  1.0f);
  Vector2D v2(1.0f, -1.0f);
  EXPECT_FLOAT_EQ(0.0f, v1.dot(v2));
}

TEST(Vector2DTest, inspect)
{
  Vector2D v1(1.23f,  -4.56f);
  EXPECT_EQ(std::string("(1.23, -4.56)"), v1.inspect());
}

TEST(Vector2DTest, length)
{
  Vector2D v1(0, 0);
  EXPECT_EQ(0.0f, v1.length());
  Vector2D v2(1, 0);
  EXPECT_EQ(1.0f, v2.length());
  Vector2D v3(0, 1);
  EXPECT_EQ(1.0f, v3.length());
  Vector2D v4(-1, 0);
  EXPECT_EQ(1.0f, v4.length());
  Vector2D v5(1, 1);
  EXPECT_EQ(1.41421356f, v5.length());
}

TEST(Vector2DTest, normalize)
{
  Vector2D v1(1.0f, 1.0f);
  EXPECT_EQ(v1, v1.normalize());
  EXPECT_FLOAT_EQ(0.7071067f, v1.x);
  EXPECT_FLOAT_EQ(0.7071067f, v1.y);
}

TEST(Vector2DTest, rotate)
{
  Vector2D v1(1.0f, 0.0f);
  EXPECT_EQ(v1, v1.rotate(M_PI * 0.5f));
  //EXPECT_FLOAT_EQ(0.0f, v1.x);
  EXPECT_NEAR(0.0f, v1.x, FLT_EPSILON);
  EXPECT_FLOAT_EQ(1.0f, v1.y);

  Vector2D v2(3.0f, 2.0f);
  EXPECT_EQ(v2, v2.rotate(M_PI * 0.5f));
  EXPECT_FLOAT_EQ(-2.0f, v2.x);
  EXPECT_FLOAT_EQ( 3.0f, v2.y);

  Vector2D v3(3.0f, 2.0f);
  EXPECT_EQ(v3, v3.rotate(M_PI * 2.0f));
  EXPECT_FLOAT_EQ(3.0f, v3.x);
  EXPECT_FLOAT_EQ(2.0f, v3.y);
}

TEST(Vector2DTest, angle)
{
  EXPECT_FLOAT_EQ(0.0f, Vector2D(1, 0).angle());
  EXPECT_FLOAT_EQ(M_PI * 2 / 8, Vector2D(1, 1).angle());
  EXPECT_FLOAT_EQ(M_PI * 2 / 4, Vector2D(0, 1).angle());
}

TEST(Vector2DTest, LSHIFT)
{
  Vector2D v1(1, 2);
  std::ostringstream oss;
  oss << v1;
  EXPECT_EQ(std::string("(1.00, 2.00)"), oss.str());
}

TEST(Vector2DTest, reflect)
{
  {
    Vector2D v1(1, 0);
    Vector2D v2(-1, 1);
    Vector2D v3(0, 1);
    EXPECT_EQ(v3, v1.reflect(v2));
  }
  {
    Vector2D v1(1, 1);
    Vector2D v2(0, 1);
    Vector2D v3(1, -1);
    EXPECT_EQ(v3, v1.reflect(v2));
  }
}
