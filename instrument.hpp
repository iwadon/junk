#ifndef INSTRUMENT_HPP_INCLUDED
#define INSTRUMENT_HPP_INCLUDED 1

#include <cstddef>
#include "channel.hpp"

class Instrument
{
public:
  static const size_t NUM_CHANNELS = 16;
  Channel &channel(int no);
private:
  Channel channels_[NUM_CHANNELS];
};

#endif // !defined(INSTRUMENT_HPP_INCLUDED)
