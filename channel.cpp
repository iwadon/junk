#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "channel.hpp"
#include "logger.hpp"

void Channel::note_on(int note, int velocity)
{
  DEBUG("note on %d %d", note, velocity);
}

void Channel::note_off(int note, int velocity)
{
  DEBUG("note off %d %d", note, velocity);
}

void Channel::polyphonic_pressure(int note, int velocity)
{
  DEBUG("polyphonic pressure %d %d", note, velocity);
}

void Channel::control_change(int no, int value)
{
  DEBUG("control change %d %d", no, value);
}

void Channel::program_change(int no)
{
  DEBUG("program change %d", no);
}

void Channel::channel_pressure(int no)
{
  DEBUG("program change %d", no);
}

void Channel::pitch_bend_change(int value)
{
  DEBUG("pitch bend change %d", value);
}
