#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator.hpp"
#include <cmath>
#include <cstdio>

static const float PI_2 = 2.0f * static_cast<float>(M_PI);

Oscillator::Oscillator()
  : sample_rate_(4.0f)
  , frequency_(1.0f)
  , phase_(0.0f)
{
  setup();
}

float Oscillator::value()
{
  float value = sinf(phase_);
  phase_ += delta_theta_;
  while (phase_ >= PI_2) {
    phase_ -= PI_2;
  }
  return value;
}

void Oscillator::set_sample_rate(const float rate)
{
  sample_rate_ = rate;
  setup();
}

void Oscillator::set_frequency(const float freq)
{
  frequency_ = freq;
  setup();
}

void Oscillator::setup()
{
  delta_theta_ = PI_2 * frequency_ / sample_rate_;
}
