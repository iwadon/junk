#ifndef FPS_HPP_INCLUDED
#define FPS_HPP_INCLUDED 1

#include <stdint.h>
#include <SDL.h>

struct FPS
{
  uint32_t next_ticks;
  uint32_t frames;
  uint32_t latest_frames;

  FPS()
    : next_ticks(0)
    , frames(0)
    , latest_frames(0)
  {
  }

  void update()
  {
    ++frames;
    uint32_t now = SDL_GetTicks();
    if (now > next_ticks) {
      latest_frames = frames;
      frames = 0;
      next_ticks += 1000;
    }
  }
};

#endif // !defined(FPS_HPP_INCLUDED)
