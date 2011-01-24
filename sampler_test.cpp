#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "sampler.hpp"

static const float data[32] = {
  -1 / 8.0f,  2 / 8.0f,  4 / 8.0f,  5 / 8.0f,  6 / 8.0f,  5 / 8.0f,  4 / 8.0f,  2 / 8.0f,
  -1 / 8.0f, -4 / 8.0f, -6 / 8.0f, -7 / 8.0f, -8 / 8.0f, -7 / 8.0f, -6 / 8.0f, -4 / 8.0f,
  -1 / 8.0f,  3 / 8.0f,  5 / 8.0f,  6 / 8.0f,  5 / 8.0f,  3 / 8.0f, -1 / 8.0f, -5 / 8.0f,
  -7 / 8.0f, -8 / 8.0f, -7 / 8.0f, -5 / 8.0f, -1 / 8.0f, -6 / 8.0f, -1 / 8.0f, -8 / 8.0f
};

class SamplerTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(SamplerTest);
  CPPUNIT_TEST(test_value);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_value();
};

void SamplerTest::test_value()
{
  Sampler s;
  s.set_data(data, sizeof data / sizeof data[0]);
  s.set_sample_rate(32.0f);
  s.set_frequency(1.0f);
  for (int i = 0; i < 10; ++i) {
    for (size_t j = 0; j < (sizeof data / sizeof data[0]); ++j) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(data[j], s.value(), 0.000001);
    }
  }
}

CPPUNIT_TEST_SUITE_REGISTRATION(SamplerTest);
