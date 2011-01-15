#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class TestOscillator : public Oscillator
{
public:
  TestOscillator()
    : Oscillator()
  {
  }
  float value()
  {
    return 0.0f;
  }
};

class OscillatorTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(OscillatorTest);
  CPPUNIT_TEST(test_value);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_value();
};

void OscillatorTest::test_value()
{
  TestOscillator osc;
  osc.set_sample_rate(4.0f);
  osc.set_frequency(1.0f);
  for (int i = 0; i < 10; ++i) {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, osc.value(), 0.0000001);
  }
}

CPPUNIT_TEST_SUITE_REGISTRATION(OscillatorTest);
