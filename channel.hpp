#ifndef CHANNEL_HPP_INCLUDED
#define CHANNEL_HPP_INCLUDED 1

#include <cstdlib>
#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST_CSTDINT_HPP)
#include <boost/cstdint.hpp>
#elif defined(HAVE_STDINT_H)
#include <stdint.h>
#endif

class Channel
{
public:
  virtual void note_on(int note, int velocity);
  virtual void note_off(int note, int velocity);
  virtual void polyphonic_pressure(int note, int velocity);
  virtual void control_change(int no, int value);
  virtual void program_change(int no);
  virtual void channel_pressure(int no);
  virtual void pitch_bend_change(int value);
  virtual bool mix_audio(uint8_t *buf, const size_t len);
};

#endif // !defined(CHANNEL_HPP_INCLUDED)
