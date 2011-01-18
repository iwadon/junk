#ifndef TRIANGLE_WAVE_OSCILLATOR_HPP_INCLUDED
#define TRIANGLE_WAVE_OSCILLATOR_HPP_INCLUDED 1

#include "oscillator.hpp"

class TriangleWaveOscillator : public Oscillator
{
public:
  TriangleWaveOscillator();
  float value();
private:
  float value_;
  float delta_;
  void setup();
};

#endif // !defined(TRIANGLE_WAVE_OSCILLATOR_HPP_INCLUDED)
