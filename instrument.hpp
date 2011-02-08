#ifndef INSTRUMENT_HPP_INCLUDED
#define INSTRUMENT_HPP_INCLUDED 1

#ifdef STDCXX_98_HEADERS
#include <cstddef>
#include <list>
#include <map>
#endif
#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST)
#include <boost/cstdint.hpp>
#elif defined(HAVE_STDINT_H)
#include <stdint.h>
#endif
#ifdef HAVE_BOOST
#include <boost/array.hpp>
#include <boost/pool/object_pool.hpp>
#endif
#include "channel.hpp"
#include "voice.hpp"

class Patch;

class Instrument
{
public:
  static const size_t NUM_CHANNELS = 16;
  static const size_t NUM_VOICES = 16;
  Instrument();
  virtual ~Instrument();
  void update();
  virtual Channel &channel(int no);
  bool mix_audio(uint8_t *buf, size_t len);
  Voice *new_voice(Channel *channel, int note, int velocity);
  void destroy_voice(Voice *voice);
  size_t stop_voices(Channel *channel, int note);
  bool set_patch(const int no, Patch *patch);
  std::string inspect() const;
private:
  boost::array<Channel *, NUM_CHANNELS> channels_;
  boost::object_pool<Voice> voice_pool_;
  std::list<Voice *> active_voices_;
  struct MixBuffer
  {
    uint8_t *addr;
    size_t len;
    MixBuffer();
    ~MixBuffer();
    bool prepare(const size_t len);
  };
  MixBuffer mix_buf_;
  std::map<int, Patch *> patches_;
};

#endif // !defined(INSTRUMENT_HPP_INCLUDED)
