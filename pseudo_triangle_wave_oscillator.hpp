#ifndef PSEUDO_TRIANGLE_WAVE_OSCILLATOR_HPP_INCLUDED
#define PSEUDO_TRIANGLE_WAVE_OSCILLATOR_HPP_INCLUDED 1

#include "oscillator.hpp"

class PseudoTriangleWaveOscillator : public Oscillator
{
public:
  PseudoTriangleWaveOscillator();
  float value();
private:
  float value_;
  float delta_;
  void setup();
};

#endif // !defined(PSEUDO_TRIANGLE_WAVE_OSCILLATOR_HPP_INCLUDED)
