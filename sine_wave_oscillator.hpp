#ifndef SINE_WAVE_OSCILLATOR_HPP_INCLUDED
#define SINE_WAVE_OSCILLATOR_HPP_INCLUDED 1

#include "oscillator.hpp"

/**
 * @brief 正弦波(サイン波)を生成するためのクラス
 *
 * @sa Oscillator
 * @sa TriangleWaveOscillator
 * @sa SawWaveOscillator
 * @sa SquareWaveOscillator
 *
 * @code
 * SineWaveOscillator osc;
 * osc.set_sample_rate(44100);
 * osc.set_frequency(440);
 * while (true) {
 *   osc.value();
 * }
 * @endcode
 */
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
