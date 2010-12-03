#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef STDCXX_98_HEADERS
#include <cstddef>
#include <iostream>
#endif
#include "logger.hpp"
#include "sdl_app.hpp"
#include "smf.hpp"

class SmfPlayApp : public SDLApp
{
public:
  SmfPlayApp();
  bool initialize(int argc, char *argv[]);
  void draw();
  void mix_audio(uint8_t *buf, size_t len);
private:
  SMF smf_;
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
  return true;
}

void SmfPlayApp::draw()
{
}

void SmfPlayApp::mix_audio(uint8_t *buf, size_t len)
{
}

int main(int argc, char *argv[])
{
  SmfPlayApp app;
  return app.run(argc, argv);
}
