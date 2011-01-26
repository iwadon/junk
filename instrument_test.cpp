#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "instrument.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "patch.hpp"

class InstrumentTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(InstrumentTest);
  CPPUNIT_TEST(test_set_patch);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_set_patch();
};

void InstrumentTest::test_set_patch()
{
  Instrument inst;
  Patch patch;
  CPPUNIT_ASSERT_EQUAL(true, inst.set_patch(0, &patch));
  CPPUNIT_ASSERT_EQUAL(false, inst.set_patch(0, &patch));
}

CPPUNIT_TEST_SUITE_REGISTRATION(InstrumentTest);
