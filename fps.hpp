/**
 * @file  fps.hpp
 * @brief FPSクラスの定義
 */

#ifndef FPS_HPP_INCLUDED
#define FPS_HPP_INCLUDED 1

#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST)
#include <boost/cstdint.hpp>
#elif defined(HAVE_STDINT_H)
#include <stdint.h>
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
