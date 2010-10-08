#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "fps.hpp"

class FpsTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(FpsTest);
  CPPUNIT_TEST(test_update);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_update();
};

void FpsTest::test_update()
{
  FPS fps;
  CPPUNIT_ASSERT_EQUAL(0U, fps.frames);
  CPPUNIT_ASSERT_EQUAL(0U, fps.latest_frames);
  fps.update();
  CPPUNIT_ASSERT_EQUAL(0U, fps.frames);
  CPPUNIT_ASSERT_EQUAL(1U, fps.latest_frames);
  sleep(1);
  fps.update();
  CPPUNIT_ASSERT_EQUAL(0U, fps.frames);
  CPPUNIT_ASSERT_EQUAL(1U, fps.latest_frames);
}

CPPUNIT_TEST_SUITE_REGISTRATION(FpsTest);
