#ifndef SMF_TRACK_HPP_INCLUDED
#define SMF_TRACK_HPP_INCLUDED 1

#define SMF_TRACK_DEBUG 1

#include <cstdlib>
#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST_CSTDINT_HPP)
#include <boost/cstdint.hpp>
#elif defined(HAVE_STDINT_H)
#include <stdint.h>
#endif

#ifdef SMF_TRACK_DEBUG
#include <string>
#endif

class SMF;
class Instrument;

class SMFTrack
{
public:
  typedef char data_type;
  enum STATE {
    STATE_NONE,
    STATE_INITIALIZED,
    STATE_PLAYING,
    STATE_STOPPED,
  };
  typedef uint32_t FLAG;
  static const FLAG FLAG_PAUSED = 1 << 0;
  SMFTrack(SMF &smf);
  void update();
  void update(Instrument &inst);
  bool setup(const data_type *data, const size_t len);
  void play();
  void stop();
  void pause();
  void resume();
  bool is_playing() const;
  bool is_paused() const;
#ifdef SMF_TRACK_DEBUG
  std::string inspect() const;
#endif
  bool mix_audio(uint8_t *buf, const size_t len);
private:
  SMF &smf_;
  const data_type *data_;
  const data_type *data_end_;
  const data_type *data_cur_;
  float wait_time_;
  STATE state_;
  FLAG flag_;
  void update_wait_time();
#ifdef SMF_TRACK_DEBUG
  void set_state(const STATE new_state);
#endif
};

#endif // !defined(SMF_TRACK_HPP_INCLUDED)
