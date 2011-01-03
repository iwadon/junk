#ifndef INSTRUMENT_HPP_INCLUDED
#define INSTRUMENT_HPP_INCLUDED 1

#include <cstddef>
#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST_CSTDINT_HPP)
#include <boost/cstdint.hpp>
#elif defined(HAVE_STDINT_H)
#include <stdint.h>
#endif
#ifdef STDCXX_98_HEADERS
#include <list>
#endif
#ifdef HAVE_BOOST
#include <boost/array.hpp>
#include <boost/pool/object_pool.hpp>
#endif
#include "channel.hpp"
#include "voice.hpp"

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
  Voice *new_voice(int note, int velocity);
  void destroy_voice(Voice *voice);
  void stop_voices(int note);
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
};

#endif // !defined(INSTRUMENT_HPP_INCLUDED)
