#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "rect.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class RectTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(RectTest);
  CPPUNIT_TEST(test_is_intersected);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_is_intersected();
};

void RectTest::test_is_intersected()
{
  Rect r1(0, 0, 10, 10);
  CPPUNIT_ASSERT_EQUAL( true, r1.is_intersected(Rect(  0,   0,  10,  10)));
  CPPUNIT_ASSERT_EQUAL( true, r1.is_intersected(Rect(  1,   1,   5,   5)));
  CPPUNIT_ASSERT_EQUAL( true, r1.is_intersected(Rect(  1,   1,  20,  20)));
  CPPUNIT_ASSERT_EQUAL( true, r1.is_intersected(Rect( 10,   0,  10,  10)));
  CPPUNIT_ASSERT_EQUAL( true, r1.is_intersected(Rect(-10,   0,  10,  10)));
  CPPUNIT_ASSERT_EQUAL( true, r1.is_intersected(Rect(  0,  10,  10,  10)));
  CPPUNIT_ASSERT_EQUAL( true, r1.is_intersected(Rect(  0, -10,  10,  10)));
  CPPUNIT_ASSERT_EQUAL(false, r1.is_intersected(Rect( 11,   0,  10,  10)));
  CPPUNIT_ASSERT_EQUAL(false, r1.is_intersected(Rect(-11,   0,  10,  10)));
  CPPUNIT_ASSERT_EQUAL(false, r1.is_intersected(Rect(  0,  11,  10,  10)));
  CPPUNIT_ASSERT_EQUAL(false, r1.is_intersected(Rect(  0, -11,  10,  10)));
}

CPPUNIT_TEST_SUITE_REGISTRATION(RectTest);
