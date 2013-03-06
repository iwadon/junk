/**
 * @file  fps.hpp
 * @brief FPSクラスの定義
 */

#ifndef FPS_HPP_INCLUDED
#define FPS_HPP_INCLUDED 1

#include <ciso646>
#if defined(_LIBCPP_VERSION) || defined(_MSC_VER)
// using libc++ or msvc
#include <cstdint>
#else
// using libstdc++ or other
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
