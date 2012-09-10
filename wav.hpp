#ifndef WAV_HPP_INCLUDED
#define WAV_HPP_INCLUDED 1

#include <SDL.h>
#include "sp.hpp"

struct Wav
{
  void *data;
  size_t len;
  Wav();
  ~Wav();
  bool LoadFile(const SP &filename);
  bool ParseData(const void *data, size_t size);
  bool ParseData(SDL_RWops *f);
  //size_t ReadSamples(void *buf, int samples);
};

#endif // !defined(WAV_HPP_INCLUDED)
