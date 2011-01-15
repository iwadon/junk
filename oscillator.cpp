#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator.hpp"

Oscillator::Oscillator()
  : sample_rate_(4.0f)
  , frequency_(1.0f)
{
  setup();
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
