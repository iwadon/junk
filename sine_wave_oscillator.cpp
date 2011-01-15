#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sine_wave_oscillator.hpp"
#include <cmath>

static const float PI_2 = 2.0f * static_cast<float>(M_PI);

SineWaveOscillator::SineWaveOscillator()
  : Oscillator()
  , phase_(0.0f)
{
}

float SineWaveOscillator::value()
{
  float value = sinf(phase_);
  phase_ += delta_theta_;
  while (phase_ >= PI_2) {
    phase_ -= PI_2;
  }
  return value;
}

void SineWaveOscillator::setup()
{
  delta_theta_ = PI_2 * frequency() / sample_rate();
}
