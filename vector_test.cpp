#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "vector.hpp"

class VectorTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(VectorTest);
  CPPUNIT_TEST(test_CTOR);
  CPPUNIT_TEST(test_ADDEQ);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_CTOR();
  void test_ADDEQ();
};

void VectorTest::test_CTOR()
{
  Vector v1;
  CPPUNIT_ASSERT_EQUAL(0.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(0.0f, v1.y);
  Vector v2(1, 2);
  CPPUNIT_ASSERT_EQUAL(1.0f, v2.x);
  CPPUNIT_ASSERT_EQUAL(2.0f, v2.y);
}

void VectorTest::test_ADDEQ()
{
  Vector v1(1, 2);
  Vector v2(3, 4);
  v1 += v2;
  CPPUNIT_ASSERT_EQUAL(4.0f, v1.x);
  CPPUNIT_ASSERT_EQUAL(6.0f, v1.y);
}

CPPUNIT_TEST_SUITE_REGISTRATION(VectorTest);
