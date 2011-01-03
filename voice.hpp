#ifndef VOICE_HPP_INCLUDED
#define VOICE_HPP_INCLUDED 1

#define VOICE_DEBUG

#ifdef STDCXX_98_HEADERS
#include <string>
#endif
#include "oscillator_stream.hpp"

class Channel;

class Voice
{
public:
  Voice(Channel *channel, int note, int velocity);
  ~Voice();
  void update();
  void play();
  void stop();
  bool is_playing() const;
  Channel *channel() const { return channel_; }
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
  Channel *channel_;
  int note_;
  int velocity_;
  OscillatorStream os_;
  float note_to_ratio(const int note);
};

#endif // !defined(VOICE_HPP_INCLUDED)
