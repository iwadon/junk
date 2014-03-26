/**
 * @file  fps.cpp
 * @brief FPSクラスの実装
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "fps.hpp"
#include <SDL.h>

/// コンストラクタ
FPS::FPS()
  : next_ticks(0)
  , frames(0)
  , latest_frames(0)
{
}

/// 更新
void FPS::update(int32_t n)
{
  frames += n;
  uint32_t now = SDL_GetTicks();
  if (now > next_ticks) {
    latest_frames = frames;
    frames = 0;
    next_ticks += 1000;
  }
}
