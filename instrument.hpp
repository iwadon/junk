#ifndef INSTRUMENT_HPP_INCLUDED
#define INSTRUMENT_HPP_INCLUDED 1

#include <cstddef>
#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST_CSTDINT_HPP)
#include <boost/cstdint.hpp>
#elif defined(HAVE_STDINT_H)
#include <stdint.h>
#endif
#include "channel.hpp"

class Instrument
{
public:
  static const size_t NUM_CHANNELS = 16;
  virtual Channel &channel(int no);
  bool mix_audio(uint8_t *buf, size_t len);
private:
  Channel channels_[NUM_CHANNELS];
};

#endif // !defined(INSTRUMENT_HPP_INCLUDED)
