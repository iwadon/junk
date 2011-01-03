#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef HAVE_BOOST
#include <boost/foreach.hpp>
#endif
#include "channel.hpp"
#include "instrument.hpp"
#include "logger.hpp"
#include "voice.hpp"

Channel::Channel(Instrument &inst, const SP &name)
  : inst_(inst)
  , name_(name.c_str())
{
}

void Channel::update()
{
}

void Channel::note_on(int note, int velocity)
{
  if (velocity == 0) {
    note_off(note, velocity);
    return;
  }
  Voice *voice = inst_.new_voice(this, note, velocity);
  if (voice == NULL) {
    ERROR("can't allocate the Voice object: note=%d, velocity=%d", note, velocity);
    return;
  }
  voice->play();
}

void Channel::note_off(int note, int /*velocity*/)
{
  inst_.stop_voices(this, note);
}

void Channel::polyphonic_pressure(int /*note*/, int /*velocity*/)
{
}

void Channel::control_change(int /*no*/, int /*value*/)
{
}

void Channel::program_change(int /*no*/)
{
}

void Channel::channel_pressure(int /*no*/)
{
}

void Channel::pitch_bend_change(int /*value*/)
{
}

std::string Channel::inspect() const
{
  char buf[64];
  snprintf(buf, sizeof buf, "#<Channel:%p %s>", this, name_.c_str());
  std::string s(buf);
  return s;
}
