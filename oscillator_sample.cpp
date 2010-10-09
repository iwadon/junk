#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sdl_app.hpp"

class OscillatorSampleApp : public SDLApp
{
public:
  OscillatorSampleApp();
protected:
  bool initialize(int argc, char *argv[]);
  void draw();
};

OscillatorSampleApp::OscillatorSampleApp()
  : SDLApp("oscillator_sample")
{
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

extern "C"
int main(int argc, char *argv[])
{
  OscillatorSampleApp app;
  return app.run(argc, argv);
}
