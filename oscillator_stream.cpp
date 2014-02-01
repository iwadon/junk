#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator_stream.hpp"
#include "oscillator_factory.hpp"
#include <cstdint>

OscillatorStream::OscillatorStream()
  : osc_(OscillatorFactory::get_instance().create("sin"))
  , volume_(1.0f)
{
}

size_t OscillatorStream::read(void *buf, const size_t len, const float freq)
{
  int16_t *p = reinterpret_cast<int16_t *>(buf);
  osc_->set_frequency(freq);
  float v = volume_ * 32767;
  for (size_t i = 0; i < (len / 2); ++i) {
    p[i] = osc_->value() * v;
  }
  return len;
}

void OscillatorStream::set_sample_rate(const float rate)
{
  osc_->set_sample_rate(rate);
}

void OscillatorStream::set_volume(const float volume)
{
  volume_ = volume;
}

void OscillatorStream::set_oscillator_type(const SP &type)
{
  oscillator_ptr_type prev_osc = osc_;
  osc_ = std::shared_ptr<Oscillator>(OscillatorFactory::get_instance().create(type.c_str()));
  osc_->set_sample_rate(prev_osc->sample_rate());
  osc_->set_frequency(prev_osc->frequency());
}
