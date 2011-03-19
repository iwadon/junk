#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "vector_2d.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "point_2d.hpp"

class Vector2DTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(Vector2DTest);
  CPPUNIT_TEST(test_CTOR);
  CPPUNIT_TEST(test_float);
  CPPUNIT_TEST(test_const_float);
  CPPUNIT_TEST(test_ADDEQ);
  CPPUNIT_TEST(test_SUBEQ);
  CPPUNIT_TEST(test_MULEQ);
  CPPUNIT_TEST(test_DIVEQ);
  CPPUNIT_TEST(test_PLUS);
  CPPUNIT_TEST(test_MINUS);
  CPPUNIT_TEST(test_ADD);
  CPPUNIT_TEST(test_MUL);
  CPPUNIT_TEST(test_EQEQ);
  CPPUNIT_TEST(test_NOTEQ);
  CPPUNIT_TEST(test_angle_length);
  CPPUNIT_TEST(test_cross);
  CPPUNIT_TEST(test_dot);
  CPPUNIT_TEST(test_length);
  CPPUNIT_TEST(test_normalize);
  CPPUNIT_TEST(test_rotate);
  CPPUNIT_TEST(test_LSHIFT);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_CTOR();
  void test_float();
  void test_const_float();
  void test_ADDEQ();
  void test_SUBEQ();
  void test_MULEQ();
  void test_DIVEQ();
  void test_PLUS();
  void test_MINUS();
  void test_ADD();
  void test_SUB();
  void test_MUL();
  void test_DIV();
  void test_EQEQ();
  void test_NOTEQ();
  void test_LSHIFT();
  void test_angle_length();
  void test_cross();
  void test_dot();
  void test_length();
  void test_normalize();
  void test_rotate();
};

void Vector2DTest::test_CTOR()
{
  Vector2D v1;
  CPPUNIT_ASSERT_EQUAL(0.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(0.0f, v1.y);
  Vector2D v2(1, 2);
  CPPUNIT_ASSERT_EQUAL(1.0f, v2.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, v2.y);
  Point2D p1(1, 2);
  Point2D p2(3, 4);
  Vector2D v4(p1, p2);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0f, v4.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0f, v4.y, 0.0000001);
}

void Vector2DTest::test_float()
{
  Vector2D v1(1.23f, 4.56f);
  float *f1 = v1;
  CPPUNIT_ASSERT_EQUAL(1.23f, f1[0]);
  CPPUNIT_ASSERT_EQUAL(4.56f, f1[1]);
}

void Vector2DTest::test_const_float()
{
  Vector2D v1(1.23f, 4.56f);
  const float *f1 = v1;
  CPPUNIT_ASSERT_EQUAL(1.23f, f1[0]);
  CPPUNIT_ASSERT_EQUAL(4.56f, f1[1]);
}

void Vector2DTest::test_ADDEQ()
{
  Vector2D v1(1, 2);
  Vector2D v2(3, 4);
  v1 += v2;
  CPPUNIT_ASSERT_EQUAL(4.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(6.0f, v1.y);
}

void Vector2DTest::test_SUBEQ()
{
  Vector2D v1(1, 2);
  Vector2D v2(3, 4);
  v1 -= v2;
  CPPUNIT_ASSERT_EQUAL(-2.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(-2.0f, v1.y);
}

void Vector2DTest::test_MULEQ()
{
  Vector2D v1(1, 2);
  v1 *= 2.5f;
  CPPUNIT_ASSERT_EQUAL(2.5f, v1.x);
  CPPUNIT_ASSERT_EQUAL(5.0f, v1.y);
  Vector2D v2(2, 1);
  v1 *= v2;
  CPPUNIT_ASSERT_EQUAL(5.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(5.0f, v1.y);
}

void Vector2DTest::test_DIVEQ()
{
  Vector2D v1(1, 2);
  v1 /= 2.5f;
  CPPUNIT_ASSERT_EQUAL(0.4f, v1.x);
  CPPUNIT_ASSERT_EQUAL(0.8f, v1.y);
  Vector2D v2(2, 1);
  v1 /= v2;
  CPPUNIT_ASSERT_EQUAL(0.2f, v1.x);
  CPPUNIT_ASSERT_EQUAL(0.8f, v1.y);
}

void Vector2DTest::test_PLUS()
{
  Vector2D v1(1.0f, 2.0f);
  CPPUNIT_ASSERT_EQUAL(v1, +v1);
}

void Vector2DTest::test_MINUS()
{
  Vector2D v1( 1.0f,  2.0f);
  Vector2D v2(-1.0f, -2.0f);
  CPPUNIT_ASSERT_EQUAL(v2, -v1);
}

void Vector2DTest::test_ADD()
{
  Vector2D v1(1, 2);
  Vector2D v2(3, 4);
  Vector2D v3 = v1 + v2;
  CPPUNIT_ASSERT_EQUAL(4.0f, v3.x);
  CPPUNIT_ASSERT_EQUAL(6.0f, v3.y);
}

void Vector2DTest::test_SUB()
{
  Vector2D v1(1, 2);
  Vector2D v2(3, 4);
  Vector2D v3 = v1 - v2;
  CPPUNIT_ASSERT_EQUAL(-2.0f, v3.x);
  CPPUNIT_ASSERT_EQUAL(-2.0f, v3.y);
}

void Vector2DTest::test_MUL()
{
  Vector2D v1(1, 2);
  Vector2D v2 = v1 * 2.5f;
  CPPUNIT_ASSERT_EQUAL(2.5f, v2.x);
  CPPUNIT_ASSERT_EQUAL(5.0f, v2.y);
  Vector2D v3(2, 1);
  Vector2D v4(1, 2);
  Vector2D v5 = v3 * v4;
  CPPUNIT_ASSERT_EQUAL(2.0f, v5.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, v5.y);
}

void Vector2DTest::test_DIV()
{
  Vector2D v1(1, 2);
  Vector2D v2 = v1 / 2.5f;
  CPPUNIT_ASSERT_EQUAL(0.4f, v2.x);
  CPPUNIT_ASSERT_EQUAL(0.8f, v2.y);
  Vector2D v3(2, 1);
  Vector2D v4(1, 2);
  Vector2D v5 = v3 / v4;
  CPPUNIT_ASSERT_EQUAL(2.0f, v5.x);
  CPPUNIT_ASSERT_EQUAL(0.5f, v5.y);
}

void Vector2DTest::test_EQEQ()
{
  Vector2D v1(1, 2);
  Vector2D v2(1, 2);
  CPPUNIT_ASSERT(v1 == v2);
  CPPUNIT_ASSERT_EQUAL(v2, v1);
}

void Vector2DTest::test_NOTEQ()
{
  Vector2D v1(1, 2);
  Vector2D v2(2, 3);
  CPPUNIT_ASSERT(v1 != v2);
}

void Vector2DTest::test_angle_length()
{
  Vector2D v1 = Vector2D::angle_length(0.0f, 1.0f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v1.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, v1.y, 0.0000001);
  v1 = Vector2D::angle_length(M_PI * 0.25f, 1.41421356f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v1.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v1.y, 0.0000001);
  v1 = Vector2D::angle_length(M_PI * 0.5f, 1.f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, v1.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v1.y, 0.0000001);
}

void Vector2DTest::test_cross()
{
  Vector2D v1(1.0f,  1.0f);
  Vector2D v2(1.0f, -1.0f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-2.0f, v1.cross(v2), 0.0000001);
}

void Vector2DTest::test_dot()
{
  Vector2D v1(1.0f,  1.0f);
  Vector2D v2(1.0f, -1.0f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, v1.dot(v2), 0.0000001);
}

void Vector2DTest::test_length()
{
  Vector2D v1(0, 0);
  CPPUNIT_ASSERT_EQUAL(0.0f, v1.length());
  Vector2D v2(1, 0);
  CPPUNIT_ASSERT_EQUAL(1.0f, v2.length());
  Vector2D v3(0, 1);
  CPPUNIT_ASSERT_EQUAL(1.0f, v3.length());
  Vector2D v4(-1, 0);
  CPPUNIT_ASSERT_EQUAL(1.0f, v4.length());
  Vector2D v5(1, 1);
  CPPUNIT_ASSERT_EQUAL(1.41421356f, v5.length());
}

void Vector2DTest::test_normalize()
{
  Vector2D v1(1.0f, 1.0f);
  CPPUNIT_ASSERT_EQUAL(v1, v1.normalize());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071067f, v1.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071067f, v1.y, 0.0000001);
}

void Vector2DTest::test_rotate()
{
  Vector2D v1(1, 0);
  CPPUNIT_ASSERT_EQUAL(v1, v1.rotate(M_PI * 0.5f));
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, v1.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v1.y, 0.0000001);
}

void Vector2DTest::test_LSHIFT()
{
  Vector2D v1(1, 2);
  std::ostringstream oss;
  oss << v1;
  CPPUNIT_ASSERT_EQUAL(std::string("(1, 2)"), oss.str());
}

CPPUNIT_TEST_SUITE_REGISTRATION(Vector2DTest);
