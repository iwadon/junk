#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "patch.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "sine_wave_oscillator.hpp"

class PatchTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(PatchTest);
  CPPUNIT_TEST(test_CTOR);
  CPPUNIT_TEST(test_set_oscillator);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_CTOR();
  void test_set_oscillator();
};

void PatchTest::test_CTOR()
{
  Patch patch;
  CPPUNIT_ASSERT(patch.oscillator() == NULL);
}

void PatchTest::test_set_oscillator()
{
  Patch patch;
  SineWaveOscillator osc;
  patch.set_oscillator(&osc);
  CPPUNIT_ASSERT(patch.oscillator() == &osc);
}

CPPUNIT_TEST_SUITE_REGISTRATION(PatchTest);
