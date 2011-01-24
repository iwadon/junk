#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sampler.hpp"

Sampler::Sampler()
  : Oscillator()
  , data_(NULL)
  , samples_(0)
  , phase_(0.0f)
  , delta_(0.0f)
{
  setup();
}

float Sampler::value()
{
  float sample = reinterpret_cast<const float *>(data_)[static_cast<int>(phase_)];
  phase_ += delta_;
  while (phase_ >= samples_) {
    phase_ -= samples_;
  }
  return sample;
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
}
