#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator.hpp"
#include <gtest/gtest.h>
#include <cfloat>

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

TEST(OscillatorTest, value)
{
  TestOscillator osc;
  osc.set_sample_rate(4.0f);
  osc.set_frequency(1.0f);
  for (int i = 0; i < 10; ++i) {
    EXPECT_NEAR(0.0f, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(0.0f, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(0.0f, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(0.0f, osc.value(), FLT_EPSILON);
  }
}
