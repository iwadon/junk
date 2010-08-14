#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <iostream>
#include <cmath>
#include "oscillator.hpp"

Oscillator::Oscillator()
  : sample_rate_(4.0f)
  , frequency_(1.0f)
  , sample_num_(0)
{
}

float Oscillator::value()
{
  int period_samples = sample_rate_ / frequency_;
  if (period_samples == 0) {
    return 0.0f;
  }
  float x = sample_num_ / static_cast<float>(period_samples);
  float value = sinf(2.0f * static_cast<float>(M_PI) * x);
  sample_num_ = (sample_num_ + 1) % period_samples;
  return value;
}

void Oscillator::set_sample_rate(const float rate)
{
  sample_rate_ = rate;
}

void Oscillator::set_frequency(const float freq)
{
  frequency_ = freq;
}
