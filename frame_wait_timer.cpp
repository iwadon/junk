#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "frame_wait_timer.hpp"
#include <SDL.h>

FrameWaitTimer::FrameWaitTimer(const int fps, const int max_skip_frames)
  : fps_(fps)
  , max_skip_frames_(max_skip_frames)
  , prev_ticks_(0)
{
}

void FrameWaitTimer::reset()
{
  prev_ticks_ = SDL_GetTicks();
}

int FrameWaitTimer::wait()
{
  float ticks = SDL_GetTicks();
  float interval = 1000.0f / fps_;
  int frames = static_cast<int>((ticks - prev_ticks_) / interval);
  if (frames <= 0) {
    frames = 1;
    SDL_Delay(static_cast<Uint32>(prev_ticks_ + interval - ticks));
    prev_ticks_ += interval;
  } else {
    if (frames > max_skip_frames_) {
      frames = max_skip_frames_;
    }
    prev_ticks_ = ticks;
  }
  return frames;
}
