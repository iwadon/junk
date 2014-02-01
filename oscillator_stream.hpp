#ifndef OSCILLATOR_STREAM_HPP_INCLUDED
#define OSCILLATOR_STREAM_HPP_INCLUDED 1

#include "audio_stream.hpp"
#include "oscillator.hpp"
#include "sp.hpp"
#include <cstddef>
#include <memory>

class OscillatorStream : public AudioStream
{
public:
  OscillatorStream();
  virtual ~OscillatorStream() {}
  virtual size_t read(void *buf, const size_t len, const float freq);
  virtual void set_sample_rate(const float rate);
  virtual void set_volume(const float volume);
  virtual void set_oscillator_type(const SP &type);
private:
  typedef std::shared_ptr<Oscillator> oscillator_ptr_type;
  oscillator_ptr_type osc_;
  float volume_;
};

#endif // !defined(OSCILLATOR_STREAM_HPP_INCLUDED)
