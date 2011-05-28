#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "filter.hpp"
#include <gtest/gtest.h>
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

TEST(FilterTest, value)
{
  TestOscillator o;
  TestFilter f;
  EXPECT_EQ(0.0f, f.value(o.value()));
}
