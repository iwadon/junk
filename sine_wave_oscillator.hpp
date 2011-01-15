#ifndef SINE_WAVE_OSCILLATOR_HPP_INCLUDED
#define SINE_WAVE_OSCILLATOR_HPP_INCLUDED 1

#include "oscillator.hpp"

class SineWaveOscillator : public Oscillator
{
public:
  SineWaveOscillator();
  float value();
private:
  float phase_;
  float delta_theta_;
  void setup();
};

#endif // !defined(SINE_WAVE_OSCILLATOR_HPP_INCLUDED)
