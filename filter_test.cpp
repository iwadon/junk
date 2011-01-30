#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "filter.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "oscillator.hpp"

class TestOscillator : public Oscillator
{
public:
  float value()
  {
    return 0.0f;
  }
};

class TestFilter : public Filter
{
public:
  float value(const float input)
  {
    return input;
  }
};

class FilterTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(FilterTest);
  CPPUNIT_TEST(test_value);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_value();
};

void FilterTest::test_value()
{
  TestOscillator o;
  TestFilter f;
  CPPUNIT_ASSERT_EQUAL(0.0f, f.value(o.value()));
}

CPPUNIT_TEST_SUITE_REGISTRATION(FilterTest);
