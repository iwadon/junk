#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sampler.hpp"

Sampler::Sampler()
  : Oscillator()
  , data_(NULL)
  , samples_(0)
  , phase_(0.0f)
{
  setup();
}

float Sampler::value()
{
  return (this->*value_impl_)();
}

void Sampler::set_data(const float *data, const size_t samples)
{
  data_ = data;
  samples_ = samples;
  setup();
}

void Sampler::setup()
{
  float prev_delta = delta_;
  delta_ = frequency() / sample_rate() * samples_;
  if (prev_delta < 0) {
    delta_ = -delta_;
  }
  if (data_ != NULL) {
    value_impl_ = &Sampler::value_sample;
  } else {
    value_impl_ = &Sampler::value_silent;
  }
}

float Sampler::value_sample()
{
  float sample = reinterpret_cast<const float *>(data_)[static_cast<int>(phase_)];
  phase_ += delta_;
  while (phase_ >= samples_) {
    phase_ -= samples_;
  }
  return sample;
}

float Sampler::value_silent()
{
  return 0.0f;
}
