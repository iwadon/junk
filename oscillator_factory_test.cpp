#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator_factory.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "oscillator.hpp"

class OscillatorFactoryTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(OscillatorFactoryTest);
  CPPUNIT_TEST(test_create);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_create();
};

void OscillatorFactoryTest::test_create()
{
  OscillatorFactory of;
  Oscillator *o = of.create("sin");
  CPPUNIT_ASSERT(o != NULL);
  o = of.create("unknown");
  CPPUNIT_ASSERT(o == NULL);
}

CPPUNIT_TEST_SUITE_REGISTRATION(OscillatorFactoryTest);
