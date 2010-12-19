#ifndef OSCILLATOR_STREAM_HPP_INCLUDED
#define OSCILLATOR_STREAM_HPP_INCLUDED 1

#ifdef STDCXX_98_HEADERS
#include <cstddef>
#endif
#include "audio_stream.hpp"
#include "oscillator.hpp"

class OscillatorStream
{
public:
  virtual size_t read(void *buf, const size_t len, const float freq);
  virtual void set_sample_rate(const float rate);
private:
  Oscillator osc_;
};

#endif // !defined(OSCILLATOR_STREAM_HPP_INCLUDED)
