#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator_stream.hpp"
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
  OscillatorStream os_;
};

OscillatorSampleApp::OscillatorSampleApp()
  : SDLApp("oscillator_sample")
{
  os_.set_sample_rate(48000);
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
  draw_str(0, 0, "Hello.");
  draw_str(0, 8, "Hello.");
  draw_str(0, 16, "Hello.");
  draw_str(100, 100, "Hello.");
  draw_chr(0, 0, 'A');
}

void OscillatorSampleApp::mix_audio(uint8_t *buf, size_t len)
{
  int16_t src[len / 2];
  os_.read(src, len / 2, 440, 1.0f);
  SDL_MixAudio(buf, reinterpret_cast<uint8_t *>(src), len, SDL_MIX_MAXVOLUME);
}

extern "C"
int main(int argc, char *argv[])
{
  OscillatorSampleApp app;
  return app.run(argc, argv);
}
