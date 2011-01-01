#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "instrument.hpp"
#ifdef HAVE_BOOST
#include <boost/foreach.hpp>
#endif
#include "channel.hpp"
#include "voice.hpp"

Instrument::Instrument()
{
  for (size_t i = 0; i < NUM_CHANNELS; ++i) {
    char buf[5];
    snprintf(buf, sizeof buf, "%2zdch", i + 1);
    channels_[i] = new Channel(*this, buf);
  }
}

void Instrument::update()
{
  BOOST_FOREACH(Channel *c, channels_) {
    c->update();
  }
  for (std::list<Voice *>::iterator i = active_voices_.begin(); i != active_voices_.end();) {
    Voice *v = *i;
    if (v->is_playing()) {
      v->update();
      ++i;
    } else {
      i = active_voices_.erase(i);
      destroy_voice(v);
    }
  }
}

Channel &Instrument::channel(int no)
{
  return *channels_[no];
}

bool Instrument::mix_audio(uint8_t *buf, const size_t len)
{
  BOOST_FOREACH(Voice *v, active_voices_) {
    v->mix_audio(buf, len);
  }
  return true;
}

Voice *Instrument::new_voice(int note, int velocity)
{
  Voice *voice = voice_pool_.construct(note, velocity);
  if (voice != NULL) {
    active_voices_.push_back(voice);
  }
  return voice;
}

void Instrument::destroy_voice(Voice *voice)
{
  active_voices_.remove(voice);
  voice_pool_.destroy(voice);
}

void Instrument::stop_voices(int note)
{
  BOOST_FOREACH(Voice *v, active_voices_) {
    if (v->note() == note) {
      v->stop();
    }
  }
}

std::string Instrument::inspect() const
{
  std::string s;
  BOOST_FOREACH(Voice *v, active_voices_) {
    s += v->inspect();
    s += "\n";
  }
  return s;
}
