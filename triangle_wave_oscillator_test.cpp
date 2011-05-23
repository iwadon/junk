#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "triangle_wave_oscillator.hpp"
#include <gtest/gtest.h>

TEST(TriangleWaveOscillatorTest, value)
{
  TriangleWaveOscillator osc;
  osc.set_sample_rate(8.0f);
  osc.set_frequency(1.0f);
  for (int i = 0; i < 10; ++i) {
    ASSERT_FLOAT_EQ( 0.0f, osc.value());
    ASSERT_FLOAT_EQ( 0.5f, osc.value());
    ASSERT_FLOAT_EQ( 1.0f, osc.value());
    ASSERT_FLOAT_EQ( 0.5f, osc.value());
    ASSERT_FLOAT_EQ( 0.0f, osc.value());
    ASSERT_FLOAT_EQ(-0.5f, osc.value());
    ASSERT_FLOAT_EQ(-1.0f, osc.value());
    ASSERT_FLOAT_EQ(-0.5f, osc.value());
  }
}
