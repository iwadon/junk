#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "instrument.hpp"
#ifdef HAVE_BOOST
#include <boost/foreach.hpp>
#endif
#include "channel.hpp"

Channel &Instrument::channel(int no)
{
  return channels_[no];
}

bool Instrument::mix_audio(uint8_t *buf, const size_t len)
{
  BOOST_FOREACH(Channel &c, channels_) {
    c.mix_audio(buf, len);
  }
  return true;
}

