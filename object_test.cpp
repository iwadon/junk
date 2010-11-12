#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
//#include "object.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class ObjectTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(ObjectTest);
  CPPUNIT_TEST(test_move);
  CPPUNIT_TEST(test_update);
  CPPUNIT_TEST(test_draw);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_move();
  void test_update();
  void test_draw();
};

void ObjectTest::test_move()
{
}

void ObjectTest::test_update()
{
}

void ObjectTest::test_draw()
{
}

CPPUNIT_TEST_SUITE_REGISTRATION(ObjectTest);
