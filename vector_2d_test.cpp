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
  CPPUNIT_TEST(test_length);
  CPPUNIT_TEST(test_inner_product);
  CPPUNIT_TEST(test_ADDEQ);
  CPPUNIT_TEST(test_ADD);
  CPPUNIT_TEST(test_MULEQ);
  CPPUNIT_TEST(test_MUL);
  CPPUNIT_TEST(test_EQEQ);
  CPPUNIT_TEST(test_NOTEQ);
  CPPUNIT_TEST(test_LSHIFT);
  CPPUNIT_TEST(test_rotate);
  CPPUNIT_TEST(test_dot);
  CPPUNIT_TEST(test_cross);
  CPPUNIT_TEST(test_normalize);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_CTOR();
  void test_length();
  void test_inner_product();
  void test_ADDEQ();
  void test_ADD();
  void test_MULEQ();
  void test_MUL();
  void test_EQEQ();
  void test_NOTEQ();
  void test_LSHIFT();
  void test_rotate();
  void test_dot();
  void test_cross();
  void test_normalize();
};

void Vector2DTest::test_CTOR()
{
  Vector2D v1;
  CPPUNIT_ASSERT_EQUAL(0.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(0.0f, v1.y);
  Vector2D v2(1, 2);
  CPPUNIT_ASSERT_EQUAL(1.0f, v2.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, v2.y);
  Vector2D v3 = Vector2D::angle_length(0.0f, 1.0f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v3.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, v3.y, 0.0000001);
  v3 = Vector2D::angle_length(M_PI * 0.25f, 1.41421356f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v3.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v3.y, 0.0000001);
  v3 = Vector2D::angle_length(M_PI * 0.5f, 1.f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, v3.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v3.y, 0.0000001);
  Point2D p1(1, 2);
  Point2D p2(3, 4);
  Vector2D v4(p1, p2);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0f, v4.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0f, v4.y, 0.0000001);
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

void Vector2DTest::test_inner_product()
{
  Vector2D v1(2, 1);
  Vector2D v2(1, 2);
  CPPUNIT_ASSERT_EQUAL(4.0f, v1.inner_product(v2));
}

void Vector2DTest::test_ADDEQ()
{
  Vector2D v1(1, 2);
  Vector2D v2(3, 4);
  v1 += v2;
  CPPUNIT_ASSERT_EQUAL(4.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(6.0f, v1.y);
}

void Vector2DTest::test_ADD()
{
  Vector2D v1(1, 2);
  Vector2D v2(3, 4);
  Vector2D v3 = v1 + v2;
  CPPUNIT_ASSERT_EQUAL(1.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, v1.y);
  CPPUNIT_ASSERT_EQUAL(3.0f, v2.x);
  CPPUNIT_ASSERT_EQUAL(4.0f, v2.y);
  CPPUNIT_ASSERT_EQUAL(4.0f, v3.x);
  CPPUNIT_ASSERT_EQUAL(6.0f, v3.y);
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

void Vector2DTest::test_MUL()
{
  Vector2D v1(1, 2);
  Vector2D v2 = v1 * 2.5f;
  CPPUNIT_ASSERT_EQUAL(1.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, v1.y);
  CPPUNIT_ASSERT_EQUAL(2.5f, v2.x);
  CPPUNIT_ASSERT_EQUAL(5.0f, v2.y);
  Vector2D v3(2, 1);
  Vector2D v4(1, 2);
  Vector2D v5 = v3 * v4;
  CPPUNIT_ASSERT_EQUAL(2.0f, v5.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, v5.y);
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

void Vector2DTest::test_LSHIFT()
{
  Vector2D v1(1, 2);
  std::ostringstream oss;
  oss << v1;
  CPPUNIT_ASSERT_EQUAL(std::string("(1, 2)"), oss.str());
}

void Vector2DTest::test_rotate()
{
  Vector2D v1(1, 0);
  CPPUNIT_ASSERT_EQUAL(v1, v1.rotate(M_PI * 0.5f));
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, v1.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v1.y, 0.0000001);
}

void Vector2DTest::test_dot()
{
  Vector2D v1(1.0f,  1.0f);
  Vector2D v2(1.0f, -1.0f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, v1.dot(v2), 0.0000001);
}

void Vector2DTest::test_cross()
{
  Vector2D v1(1.0f,  1.0f);
  Vector2D v2(1.0f, -1.0f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-2.0f, v1.cross(v2), 0.0000001);
}

void Vector2DTest::test_normalize()
{
  Vector2D v1(1.0f, 1.0f);
  CPPUNIT_ASSERT_EQUAL(v1, v1.normalize());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071067f, v1.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071067f, v1.y, 0.0000001);
}

CPPUNIT_TEST_SUITE_REGISTRATION(Vector2DTest);
