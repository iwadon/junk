#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "triangle_wave_oscillator.hpp"

TriangleWaveOscillator::TriangleWaveOscillator()
  : Oscillator()
  , value_(0.0f)
{
}

float TriangleWaveOscillator::value()
{
  float value = value_;
  value_ += delta_;
  if (value_ >= 1.0f) {
    delta_ = -delta_;
    value_ = 1.0f - (value_ - 1.0f);
  } else if (value_ <= -1.0f) {
    delta_ = -delta_;
    value_ = -1.0f + (value_ + 1.0f);
  }
  return value;
}

void TriangleWaveOscillator::setup()
{
  float prev_delta = delta_;
  delta_ = frequency() / sample_rate() * 4;
  if (prev_delta < 0) {
    delta_ = -delta_;
  }
}
