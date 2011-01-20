#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "pseudo_triangle_wave_oscillator.hpp"
#include <cstddef>

static const size_t VALUE_TABLE_SIZE = 32;
static const float value_table[VALUE_TABLE_SIZE] = {
#if 1
   0 * 1.0f / 15,  1 * 1.0f / 15,  2 * 1.0f / 15,  3 * 1.0f / 15,
   4 * 1.0f / 15,  5 * 1.0f / 15,  6 * 1.0f / 15 , 7 * 1.0f / 15,
   8 * 1.0f / 15,  9 * 1.0f / 15, 10 * 1.0f / 15, 11 * 1.0f / 15,
  12 * 1.0f / 15, 13 * 1.0f / 15, 14 * 1.0f / 15, 15 * 1.0f / 15,
  15 * 1.0f / 15, 14 * 1.0f / 15, 13 * 1.0f / 15, 12 * 1.0f / 15,
  11 * 1.0f / 15, 10 * 1.0f / 15,  9 * 1.0f / 15,  8 * 1.0f / 15,
   7 * 1.0f / 15,  6 * 1.0f / 15,  5 * 1.0f / 15 , 4 * 1.0f / 15,
   3 * 1.0f / 15,  2 * 1.0f / 15,  1 * 1.0f / 15,  0 * 1.0f / 15,
#endif
#if 0
   -7 / 7.0f, -6 / 7.0f, -5 / 7.0f, -4 / 7.0f, -3 / 7.0f, -2 / 7.0f, -1 / 7.0f,  0 / 7.0f,
    0 / 7.0f,  1 / 7.0f,  2 / 7.0f,  3 / 7.0f,  4 / 7.0f,  5 / 7.0f,  6 / 7.0f,  7 / 7.0f,
    7 / 7.0f,  6 / 7.0f,  5 / 7.0f,  4 / 7.0f,  3 / 7.0f,  2 / 7.0f,  1 / 7.0f,  0 / 7.0f,
    0 / 7.0f, -1 / 7.0f, -2 / 7.0f, -3 / 7.0f, -4 / 7.0f, -5 / 7.0f, -6 / 7.0f, -7 / 7.0f,
#endif
#if 0
     1 / 15.0f,   3 / 15.0f,   5 / 15.0f,   7 / 15.0f,   9 / 15.0f,  11 / 15.0f,  13 / 15.0f,  15 / 15.0f,
    15 / 15.0f,  13 / 15.0f,  11 / 15.0f,   9 / 15.0f,   7 / 15.0f,   5 / 15.0f,   3 / 15.0f,   1 / 15.0f,
    -1 / 15.0f,  -3 / 15.0f,  -5 / 15.0f,  -7 / 15.0f,  -9 / 15.0f, -11 / 15.0f, -13 / 15.0f, -15 / 15.0f,
   -15 / 15.0f, -13 / 15.0f, -11 / 15.0f,  -9 / 15.0f,  -7 / 15.0f,  -5 / 15.0f,  -3 / 15.0f,  -1 / 15.0f,
#endif
};

PseudoTriangleWaveOscillator::PseudoTriangleWaveOscillator()
  : Oscillator()
  , value_(0.0f)
{
}

float PseudoTriangleWaveOscillator::value()
{
  float value = value_table[static_cast<int>(value_)];
  value_ += delta_;
  if (value_ >= VALUE_TABLE_SIZE) {
    value_ -= VALUE_TABLE_SIZE;
  }
  return value;
}

void PseudoTriangleWaveOscillator::setup()
{
  float prev_delta = delta_;
  delta_ = frequency() / sample_rate() * VALUE_TABLE_SIZE / 2;
  if (prev_delta < 0) {
    delta_ = -delta_;
  }
}
