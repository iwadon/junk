#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <iostream>
#include "logger.hpp"
#include "instrument.hpp"
#include "smf.hpp"

class Dumper : public ::Instrument
{
public:
  class Channel : public ::Channel
  {
    void note_on(int note, int velocity);
    void note_off(int note, int velocity);
    void polyphonic_pressure(int note, int velocity);
    void control_change(int no, int value);
    void program_change(int no);
    void channel_pressure(int no);
    void pitch_bend_change(int value);
  };
  Channel &channel(int no) { return channels_[no]; }
private:
  Channel channels_[NUM_CHANNELS];
};

void Dumper::Channel::note_on(int note, int velocity)
{
  DEBUG("dump note on %d %d", note, velocity);
}

void Dumper::Channel::note_off(int note, int velocity)
{
  DEBUG("dump note off %d %d", note, velocity);
}

void Dumper::Channel::polyphonic_pressure(int note, int velocity)
{
  DEBUG("dump polyphonic pressure %d %d", note, velocity);
}

void Dumper::Channel::control_change(int no, int value)
{
  DEBUG("dump control change %d %d", no, value);
}

void Dumper::Channel::program_change(int no)
{
  DEBUG("dump program change %d", no);
}

void Dumper::Channel::channel_pressure(int no)
{
  DEBUG("dump program change %d", no);
}

void Dumper::Channel::pitch_bend_change(int value)
{
  DEBUG("dump pitch bend change %d", value);
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " FILE" << std::endl;
    return 1;
  }
  Dumper dmp;
  SMF smf;
  smf.set_instrument(&dmp);
  if (!smf.load_file(argv[1])) {
    ERROR("Failed to load file: %s", argv[1]);
    return 1;
  }
  smf.play();
  while (smf.is_playing()) {
    smf.update();
  }
  return 0;
}
