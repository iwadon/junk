#ifndef OSCILLATOR_HPP_INCLUDED
#define OSCILLATOR_HPP_INCLUDED 1

class Oscillator
{
public:
  Oscillator();
  float value();
  void set_sample_rate(const float rate);
  void set_frequency(const float freq);
private:
  float sample_rate_;
  float frequency_;
  int sample_num_;
};

#endif // !defined(OSCILLATOR_HPP_INCLUDED)
