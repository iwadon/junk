#ifndef WAV_HPP_INCLUDED
#define WAV_HPP_INCLUDED 1

#include "sp.hpp"

struct Wav
{
  void *data;
  size_t len;
  bool LoadFile(const SP &filename);
  //size_t ReadSamples(void *buf, int samples);
};

#endif // !defined(WAV_HPP_INCLUDED)
