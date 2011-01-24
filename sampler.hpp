#ifndef SAMPLER_HPP_INCLUDED
#define SAMPLER_HPP_INCLUDED 1

#ifdef STDCXX_98_HEADERS
#include <cstddef>
#endif
#include "oscillator.hpp"

class Sampler : public Oscillator
{
public:
  Sampler();
  float value();
  void set_data(const float *data, const size_t samples);
protected:
  void setup();
private:
  const float *data_;
  size_t samples_;
  float phase_;
  float delta_;
  float (Sampler::*value_impl_)();
  float value_sample();
  float value_silent();
};

#endif // !defined(SAMPLER_HPP_INCLUDED)
