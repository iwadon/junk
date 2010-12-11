#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef STDCXX_98_HEADERS
#include <cstddef>
#include <iostream>
#endif
#include "instrument.hpp"
#include "logger.hpp"
#include "sdl_app.hpp"
#include "smf.hpp"

class SmfPlayApp : public SDLApp
{
public:
  SmfPlayApp();
  bool initialize(int argc, char *argv[]);
  void update();
  void draw();
  void mix_audio(uint8_t *buf, size_t len);
private:
  SMF smf_;
  Instrument inst_;
};

SmfPlayApp::SmfPlayApp()
  : SDLApp("SMF Play")
{
}

bool SmfPlayApp::initialize(int argc, char *argv[])
{
  if (!load_font_file("data/font5x5.png")) {
    return false;
  }
  if (argc >= 2 && !smf_.load_file(argv[1])) {
    return false;
  }
  smf_.play();
  return true;
}

void SmfPlayApp::update()
{
  smf_.update();
}

void SmfPlayApp::draw()
{
  draw_strf(8, 24, "%s", smf_.is_playing() ? "PLAYING" : "-");
}

void SmfPlayApp::mix_audio(uint8_t *buf, size_t len)
{
  //SDL_MixAudio(buf, smf_.mixed_data(len), len, SDL_MIX_MAXVOLUME);
}

int main(int argc, char *argv[])
{
  SmfPlayApp app;
  return app.run(argc, argv);
}
