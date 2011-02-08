#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "vector.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class VectorTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(VectorTest);
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
};

void VectorTest::test_CTOR()
{
  Vector v1;
  CPPUNIT_ASSERT_EQUAL(0.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(0.0f, v1.y);
  Vector v2(1, 2);
  CPPUNIT_ASSERT_EQUAL(1.0f, v2.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, v2.y);
  Vector v3 = Vector::angle_length(0.0f, 1.0f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v3.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, v3.y, 0.0000001);
  v3 = Vector::angle_length(M_PI * 0.25f, 1.41421356f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v3.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v3.y, 0.0000001);
  v3 = Vector::angle_length(M_PI * 0.5f, 1.f);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, v3.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v3.y, 0.0000001);
}

void VectorTest::test_length()
{
  Vector v1(0, 0);
  CPPUNIT_ASSERT_EQUAL(0.0f, v1.length());
  Vector v2(1, 0);
  CPPUNIT_ASSERT_EQUAL(1.0f, v2.length());
  Vector v3(0, 1);
  CPPUNIT_ASSERT_EQUAL(1.0f, v3.length());
  Vector v4(-1, 0);
  CPPUNIT_ASSERT_EQUAL(1.0f, v4.length());
  Vector v5(1, 1);
  CPPUNIT_ASSERT_EQUAL(1.41421356f, v5.length());
}

void VectorTest::test_inner_product()
{
  Vector v1(2, 1);
  Vector v2(1, 2);
  CPPUNIT_ASSERT_EQUAL(4.0f, v1.inner_product(v2));
}

void VectorTest::test_ADDEQ()
{
  Vector v1(1, 2);
  Vector v2(3, 4);
  v1 += v2;
  CPPUNIT_ASSERT_EQUAL(4.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(6.0f, v1.y);
}

void VectorTest::test_ADD()
{
  Vector v1(1, 2);
  Vector v2(3, 4);
  Vector v3 = v1 + v2;
  CPPUNIT_ASSERT_EQUAL(1.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, v1.y);
  CPPUNIT_ASSERT_EQUAL(3.0f, v2.x);
  CPPUNIT_ASSERT_EQUAL(4.0f, v2.y);
  CPPUNIT_ASSERT_EQUAL(4.0f, v3.x);
  CPPUNIT_ASSERT_EQUAL(6.0f, v3.y);
}

void VectorTest::test_MULEQ()
{
  Vector v1(1, 2);
  v1 *= 2.5f;
  CPPUNIT_ASSERT_EQUAL(2.5f, v1.x);
  CPPUNIT_ASSERT_EQUAL(5.0f, v1.y);
  Vector v2(2, 1);
  v1 *= v2;
  CPPUNIT_ASSERT_EQUAL(5.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(5.0f, v1.y);
}

void VectorTest::test_MUL()
{
  Vector v1(1, 2);
  Vector v2 = v1 * 2.5f;
  CPPUNIT_ASSERT_EQUAL(1.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, v1.y);
  CPPUNIT_ASSERT_EQUAL(2.5f, v2.x);
  CPPUNIT_ASSERT_EQUAL(5.0f, v2.y);
  Vector v3(2, 1);
  Vector v4(1, 2);
  Vector v5 = v3 * v4;
  CPPUNIT_ASSERT_EQUAL(2.0f, v5.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, v5.y);
}

void VectorTest::test_EQEQ()
{
  Vector v1(1, 2);
  Vector v2(1, 2);
  CPPUNIT_ASSERT(v1 == v2);
  CPPUNIT_ASSERT_EQUAL(v2, v1);
}

void VectorTest::test_NOTEQ()
{
  Vector v1(1, 2);
  Vector v2(2, 3);
  CPPUNIT_ASSERT(v1 != v2);
}

void VectorTest::test_LSHIFT()
{
  Vector v1(1, 2);
  std::ostringstream oss;
  oss << v1;
  CPPUNIT_ASSERT_EQUAL(std::string("(1, 2)"), oss.str());
}

void VectorTest::test_rotate()
{
  Vector v1(1, 0);
  CPPUNIT_ASSERT_EQUAL(v1, v1.rotate(M_PI * 0.5f));
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, v1.x, 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, v1.y, 0.0000001);
}

CPPUNIT_TEST_SUITE_REGISTRATION(VectorTest);
