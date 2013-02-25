/**
 * @file  fps.hpp
 * @brief FPSクラスの定義
 */

#ifndef FPS_HPP_INCLUDED
#define FPS_HPP_INCLUDED 1

#ifdef _MSC_VER
#include <cstdint>
#else
#include <tr1/cstdint>
#endif

/// fpsを測る
struct FPS
{
  uint32_t next_ticks;		///< 次回の時刻
  uint32_t frames;		///< 現在のフレーム数
  uint32_t latest_frames;	///< 直前のfps

  FPS();
  void update();
};

#endif // !defined(FPS_HPP_INCLUDED)
