#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cassert>
#include <cmath>
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
  os_.read(buf, len, 440 * note_to_ratio(note_));
  return true;
}

float Voice::note_to_ratio(const int note)
{
  assert(note >= 0);
  assert(note <= 127);
  static const float note_ratios[12] = {
    1.000000f, 1.059463f, 1.122462f, 1.189207f, 1.259921f, 1.334840f,
    1.414214f, 1.498307f, 1.587401f, 1.681793f, 1.781797f, 1.887749f
  };
  static const float octave_ratios[11] = {
    0.3125f, 0.0625f, 0.125f, 0.25f, 0.5f, 1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f
  };
  int n = note - 9;
  int o = n / 12;
  if (n < 0) {
    n += 12;
    --o;
  }
  assert(o >= 0);
  assert(o <= 10);
  return note_ratios[n % 12] * octave_ratios[o];
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
