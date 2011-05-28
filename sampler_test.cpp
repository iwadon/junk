#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sampler.hpp"
#include <cfloat>
#include <gtest/gtest.h>

static const float data[32] = {
  -1 / 8.0f,  2 / 8.0f,  4 / 8.0f,  5 / 8.0f,  6 / 8.0f,  5 / 8.0f,  4 / 8.0f,  2 / 8.0f,
  -1 / 8.0f, -4 / 8.0f, -6 / 8.0f, -7 / 8.0f, -8 / 8.0f, -7 / 8.0f, -6 / 8.0f, -4 / 8.0f,
  -1 / 8.0f,  3 / 8.0f,  5 / 8.0f,  6 / 8.0f,  5 / 8.0f,  3 / 8.0f, -1 / 8.0f, -5 / 8.0f,
  -7 / 8.0f, -8 / 8.0f, -7 / 8.0f, -5 / 8.0f, -1 / 8.0f, -6 / 8.0f, -1 / 8.0f, -8 / 8.0f
};

TEST(SamplerTest, value)
{
  Sampler s;
  s.set_data(data, sizeof data / sizeof data[0]);
  s.set_sample_rate(32.0f);
  s.set_frequency(1.0f);
  for (int i = 0; i < 10; ++i) {
    for (size_t j = 0; j < (sizeof data / sizeof data[0]); ++j) {
      EXPECT_NEAR(data[j], s.value(), FLT_EPSILON);
    }
  }
  s.set_data(NULL, 0);
  for (int i = 0; i < 100; ++i) {
    EXPECT_NEAR(0.0f, s.value(), FLT_EPSILON);
  }
}
