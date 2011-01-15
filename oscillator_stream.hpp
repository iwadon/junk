#ifndef OSCILLATOR_STREAM_HPP_INCLUDED
#define OSCILLATOR_STREAM_HPP_INCLUDED 1

#ifdef STDCXX_98_HEADERS
#include <cstddef>
#endif
#ifdef HAVE_BOOST
#include <boost/shared_ptr.hpp>
#endif
#include "audio_stream.hpp"
#include "oscillator.hpp"

class OscillatorStream
{
public:
  OscillatorStream();
  virtual ~OscillatorStream() {}
  virtual size_t read(void *buf, const size_t len, const float freq, const float volume);
  virtual void set_sample_rate(const float rate);
private:
  boost::shared_ptr<Oscillator> osc_;
};

#endif // !defined(OSCILLATOR_STREAM_HPP_INCLUDED)
