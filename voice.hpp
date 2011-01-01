#ifndef VOICE_HPP_INCLUDED
#define VOICE_HPP_INCLUDED 1

#define VOICE_DEBUG

#ifdef STDCXX_98_HEADERS
#include <string>
#endif
#include "oscillator_stream.hpp"

class Voice
{
public:
  Voice(int note, int velocity);
  ~Voice();
  void update();
  void play();
  void stop();
  bool is_playing() const;
  int note() const { return note_; }
  bool mix_audio(uint8_t *buf, const size_t len);
#ifdef VOICE_DEBUG
  std::string inspect() const;
#endif
private:
  enum STATE {
    STATE_NONE,
    STATE_PLAYING,
    STATE_STOPPING,
    NUM_STATES
  };
  STATE state_;
  int note_;
  int velocity_;
  OscillatorStream os_;
};

#endif // !defined(VOICE_HPP_INCLUDED)
