#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sine_wave_oscillator.hpp"
#include <gtest/gtest.h>
#include <cfloat>

TEST(SineWaveOscillatorTest, value)
{
  SineWaveOscillator osc;
  osc.set_sample_rate(4.0f);
  osc.set_frequency(1.0f);
  for (int i = 0; i < 10; ++i) {
    EXPECT_NEAR( 0.0f, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 1.0f, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 0.0f, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(-1.0f, osc.value(), FLT_EPSILON);
  }
}
