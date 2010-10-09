#ifndef FPS_HPP_INCLUDED
#define FPS_HPP_INCLUDED 1

#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST_CSTDINT_HPP)
#include <boost/cstdint.hpp>
#endif

struct FPS
{
  uint32_t next_ticks;
  uint32_t frames;
  uint32_t latest_frames;

  FPS();
  void update();
};

#endif // !defined(FPS_HPP_INCLUDED)
