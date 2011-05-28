#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "pseudo_triangle_wave_oscillator.hpp"
#include <gtest/gtest.h>
#include <cfloat>

TEST(PseudoTriangleWaveOscillatorTest, value)
{
  PseudoTriangleWaveOscillator osc;
  osc.set_sample_rate(32.0f);
  osc.set_frequency(1.0f);
  for (int i = 0; i < 10; ++i) {
    EXPECT_NEAR(  0.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  1.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  2.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  3.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  4.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  5.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  6.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  7.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  8.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  9.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 10.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 11.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 12.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 13.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 14.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 15.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 15.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 14.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 13.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 12.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 11.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR( 10.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  9.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  8.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  7.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  6.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  5.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  4.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  3.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  2.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  1.0f / 15, osc.value(), FLT_EPSILON);
    EXPECT_NEAR(  0.0f / 15, osc.value(), FLT_EPSILON);
  }
}
