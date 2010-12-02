#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "instrument.hpp"
#include "channel.hpp"

Channel &Instrument::channel(int no)
{
  return channels_[no];
}
