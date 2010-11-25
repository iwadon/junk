#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator.hpp"
#include "sdl_app.hpp"

class OscillatorSampleApp : public SDLApp
{
public:
  OscillatorSampleApp();
protected:
  bool initialize(int argc, char *argv[]);
  void draw();
  void mix_audio(uint8_t *buf, size_t len);
private:
  Oscillator osc_;
};

OscillatorSampleApp::OscillatorSampleApp()
  : SDLApp("oscillator_sample")
{
  osc_.set_sample_rate(48000);
  osc_.set_frequency(440);
}

bool OscillatorSampleApp::initialize(int /*argc*/, char */*argv*/[])
{
  if (!load_font_file("data/font5x5.png")) {
    return false;
  }
  return true;
}

void OscillatorSampleApp::draw()
{
  draw_string(0, 0, "Hello.");
  draw_string(0, 8, "Hello.");
  draw_string(0, 16, "Hello.");
  draw_string(100, 100, "Hello.");
  draw_chr(0, 0, 'A');
}

void OscillatorSampleApp::mix_audio(uint8_t *buf, size_t len)
{
  int16_t src[len / 2];
  for (size_t i = 0; i < len / 2; ++i) {
    src[i] = osc_.value() * 32767;
  }
  SDL_MixAudio(buf, reinterpret_cast<uint8_t *>(src), len, SDL_MIX_MAXVOLUME);
}

extern "C"
int main(int argc, char *argv[])
{
  OscillatorSampleApp app;
  return app.run(argc, argv);
}
