#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "pseudo_triangle_wave_oscillator.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class PseudoTriangleWaveOscillatorTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(PseudoTriangleWaveOscillatorTest);
  CPPUNIT_TEST(test_value);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_value();
};

void PseudoTriangleWaveOscillatorTest::test_value()
{
  PseudoTriangleWaveOscillator osc;
  osc.set_sample_rate(32.0f);
  osc.set_frequency(1.0f);
  for (int i = 0; i < 10; ++i) {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  0.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  2.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  3.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  6.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  7.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  8.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  9.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 10.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 11.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 12.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 13.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 14.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 15.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 15.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 14.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 13.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 12.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 11.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 10.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  9.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  8.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  7.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  6.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  5.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  4.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  3.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  2.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  1.0f / 15, osc.value(), 0.0000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(  0.0f / 15, osc.value(), 0.0000001);
  }
}

CPPUNIT_TEST_SUITE_REGISTRATION(PseudoTriangleWaveOscillatorTest);
