#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cassert>
#include <cmath>
#include "voice.hpp"
#include "logger.hpp"

Voice::Voice(Channel *channel, int note, int velocity)
  : state_(STATE_NONE)
  , channel_(channel)
  , note_(note)
  , velocity_(velocity)
{
  os_.set_sample_rate(48000);
  os_.set_oscillator_type("sin");
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
  os_.set_volume(velocity_ / 127.0f * 0.1f);
  os_.read(buf, len, 440 * note_to_ratio(note_));
  return true;
}

float Voice::note_to_ratio(const int note)
{
  assert(note >= 0);
  assert(note <= 127);
  static const float note_ratios[12] = {
    0.594604f, 0.629961f, 0.667420f, 0.707107f, 0.749154f, 0.793701f,
    0.840896f, 0.890899f, 0.943874f, 1.000000f, 1.059463f, 1.122462f
  };
  static const float octave_ratios[11] = {
    1.0f / 32, 1.0f / 16, 1.0f / 8, 1.0f / 4, 1.0f / 2, 1.0f, 1.0f * 2, 1.0f * 4, 1.0f * 8, 1.0f * 16, 1.0f * 32
  };
  int o = note / 12;
  if (note < 0) {
    --o;
  }
  int n = note % 12;
  assert(n >= 0);
  assert(n <= 11);
  assert(o >= 0);
  assert(o <= 10);
  return note_ratios[n] * octave_ratios[o];
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
