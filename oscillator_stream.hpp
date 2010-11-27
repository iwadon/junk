#ifndef OSCILLATOR_STREAM_HPP_INCLUDED
#define OSCILLATOR_STREAM_HPP_INCLUDED 1

#include "audio_stream.hpp"
#include <cstddef>
#include "oscillator.hpp"

class OscillatorStream
{
public:
  virtual size_t read(void *buf, const size_t len, const float ratio);
  virtual void set_sample_rate(const float rate);
private:
  Oscillator osc_;
};

#endif // !defined(OSCILLATOR_STREAM_HPP_INCLUDED)
