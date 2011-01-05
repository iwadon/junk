#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator_stream.hpp"
#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST_CSTDINT_HPP)
#include <boost/cstdint.hpp>
#elif defined(HAVE_STDINT_H)
#include <stdint.h>
#endif
#include "logger.hpp"

size_t OscillatorStream::read(void *buf, const size_t len, const float freq, const float volume)
{
  //INFO("%s: buf=%p, len=%zu, freq=%f", __PRETTY_FUNCTION__, buf, len, freq);
  int16_t *p = reinterpret_cast<int16_t *>(buf);
  osc_.set_frequency(freq);
  float v = volume * 32767;
  for (size_t i = 0; i < (len / 2); ++i) {
    p[i] = osc_.value() * v;
  }
  return len;
}

void OscillatorStream::set_sample_rate(const float rate)
{
  osc_.set_sample_rate(rate);
}
