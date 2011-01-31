#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "instrument.hpp"
#ifdef HAVE_BOOST
#include <boost/foreach.hpp>
#endif
#include <SDL.h>
#include "channel.hpp"
#include "logger.hpp"
#include "patch.hpp"
#include "voice.hpp"

Instrument::Instrument()
{
  for (size_t i = 0; i < NUM_CHANNELS; ++i) {
    char buf[5];
    snprintf(buf, sizeof buf, "%2zdch", i + 1);
    channels_[i] = new Channel(*this, buf);
  }
}

Instrument::~Instrument()
{
  for (size_t i = 0; i < NUM_CHANNELS; ++i) {
    delete channels_[i];
  }
}

void Instrument::update()
{
  BOOST_FOREACH(Channel *c, channels_) {
    c->update();
  }
  SDL_LockAudio();
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
  SDL_UnlockAudio();
}

Channel &Instrument::channel(int no)
{
  return *channels_[no];
}

bool Instrument::mix_audio(uint8_t *buf, const size_t len)
{
  if (!mix_buf_.prepare(len)) {
    return false;
  }
  BOOST_FOREACH(Voice *v, active_voices_) {
    v->mix_audio(mix_buf_.addr, mix_buf_.len);
    SDL_MixAudio(buf, mix_buf_.addr, len, SDL_MIX_MAXVOLUME);
  }
  return true;
}

Voice *Instrument::new_voice(Channel *channel, int note, int velocity)
{
  Voice *voice = voice_pool_.construct(channel, note, velocity);
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

size_t Instrument::stop_voices(Channel *channel, int note)
{
  size_t n = 0;
  BOOST_FOREACH(Voice *v, active_voices_) {
    if (v->channel() == channel && v->note() == note) {
      v->stop();
      ++n;
    }
  }
  return n;
}

bool Instrument::set_patch(const int no, Patch *patch)
{
  if (patches_.count(no) > 0) {
    return false;
  }
  patches_[no] = patch;
  return true;
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

Instrument::MixBuffer::MixBuffer()
  : addr(NULL)
  , len(0)
{
}

Instrument::MixBuffer::~MixBuffer()
{
  SDL_free(addr);
}

bool Instrument::MixBuffer::prepare(const size_t new_len)
{
  if (new_len != len) {
    if (addr != NULL) {
      SDL_free(addr);
    }
    addr = reinterpret_cast<uint8_t *>(SDL_malloc(new_len));
    if (addr == NULL) {
      SDL_ERROR("SDL_malloc");
      len = 0;
      return false;
    }
    INFO("Mix buffer size has changed: %zu -> %zu", len, new_len);
    len = new_len;
  }
  return true;
}
