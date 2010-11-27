#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator_stream.hpp"
#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST_CSTDINT_HPP)
#include <boost/cstdint.hpp>
#endif

size_t OscillatorStream::read(void *buf, const size_t len, const float ratio)
{
  int16_t *p = reinterpret_cast<int16_t *>(buf);
  osc_.set_frequency(ratio);
  for (size_t i = 0; i < len; ++i) {
    p[i] = osc_.value() * 32767;
  }
    return len;
}
