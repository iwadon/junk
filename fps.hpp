/**
 * @file  fps.hpp
 * @brief FPSクラスの定義
 */

#ifndef FPS_HPP_INCLUDED
#define FPS_HPP_INCLUDED 1

#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST_CSTDINT_HPP)
#include <boost/cstdint.hpp>
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
