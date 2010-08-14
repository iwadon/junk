#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "oscillator.hpp"

class OscillatorTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(OscillatorTest);
  CPPUNIT_TEST(test_update);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_update();
};

void OscillatorTest::test_update()
{
  Oscillator osc;
  osc.set_sample_rate(4.0f);
  osc.set_frequency(1.0f);
  for (int i = 0; i < 10; ++i) {
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0f, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0f, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0f, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0f, osc.value(), 0.0000001);
  }
}

CPPUNIT_TEST_SUITE_REGISTRATION(OscillatorTest);
