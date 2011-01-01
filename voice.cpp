#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "voice.hpp"
#include "logger.hpp"

Voice::Voice(int note, int velocity)
  : state_(STATE_NONE)
  , note_(note)
  , velocity_(velocity)
{
  os_.set_sample_rate(48000);
}

Voice::~Voice()
{
}

void Voice::update()
{
  if (state_ == STATE_STOPPING) {
    state_ = STATE_NONE;
  }
}

void Voice::play()
{
  state_ = STATE_PLAYING;
}

void Voice::stop()
{
  state_ = STATE_STOPPING;
}

bool Voice::is_playing() const
{
  return state_ != STATE_NONE;
}

bool Voice::mix_audio(uint8_t *buf, const size_t len)
{
  os_.read(buf, len / 2, 440);
  return true;
}

#ifdef VOICE_DEBUG

std::string Voice::inspect() const
{
  static const char *state_name[NUM_STATES] = {
    "NONE", "PLAYING", "STOPPING"
  };
  static const char *note_name[12] = {
    "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
  };
  char buf[64];
  snprintf(buf, sizeof buf, "#<Voice:%p %8s %2s%d %d>", this, state_name[state_], note_name[note_ % 12], (note_ / 12) - 1, velocity_);
  std::string s(buf);
  return s;
}

#endif // defined(VOICE_DEBUG)
