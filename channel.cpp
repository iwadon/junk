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
  //DEBUG("%s note on  %3d %3d", name_.c_str(), note, velocity);
  Voice *voice = inst_.new_voice(this, note, velocity);
  if (voice == NULL) {
    LOG_ERROR("can't allocate the Voice object: note=%d, velocity=%d", note, velocity);
    return;
  }
  voice->play();
}

void Channel::note_off(int note, int velocity)
{
  size_t n = inst_.stop_voices(this, note);
  //DEBUG("%s note off %3d %3d %u", name_.c_str(), note, velocity, n);
  if (n == 0) {
    LOG_WARN("n == 0");
  }
}

void Channel::polyphonic_pressure(int /*note*/, int /*velocity*/)
{
  LOG_INFO("Polyphonic Pressure event is not implemented yet.");
}

void Channel::control_change(int no, int value)
{
  LOG_INFO("Control Change event is not implemented yet: CC%03d %3d", no, value);
}

void Channel::program_change(int /*no*/)
{
  LOG_INFO("Program Change event is not implemented yet.");
}

void Channel::channel_pressure(int /*no*/)
{
  LOG_INFO("Channel Pressure event is not implemented yet.");
}

void Channel::pitch_bend_change(int /*value*/)
{
  LOG_INFO("Pitch Bend Change event is not implemented yet.");
}

std::string Channel::inspect() const
{
  char buf[64];
  snprintf(buf, sizeof buf, "#<Channel:%p %s>", this, name_.c_str());
  std::string s(buf);
  return s;
}
