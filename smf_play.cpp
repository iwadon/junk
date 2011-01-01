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
  ~SmfPlayApp();
  bool initialize(int argc, char *argv[]);
  void update();
  void draw();
  void mix_audio(uint8_t *buf, size_t len);
private:
  SMF smf_;
  Instrument inst_;
  uint8_t *mix_buf_;
  size_t mix_buf_len_;
  bool initialize_mix_buf(const size_t len);
};

SmfPlayApp::SmfPlayApp()
  : SDLApp("SMF Play")
  , mix_buf_(NULL)
  , mix_buf_len_(0)
{
}

SmfPlayApp::~SmfPlayApp()
{
  SDL_free(mix_buf_);
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
  //draw_strf(8, 24, "%s", smf_.is_playing() ? "PLAYING" : "-");
  draw_strf(8, 32, "%s", smf_.inspect().c_str());
}

void SmfPlayApp::mix_audio(uint8_t *buf, size_t len)
{
  if (!initialize_mix_buf(len)) {
    return;
  }
  smf_.mix_audio(buf, len);
  //SDL_MixAudio(buf, smf_.mixed_data(len), len, SDL_MIX_MAXVOLUME);
}

bool SmfPlayApp::initialize_mix_buf(const size_t len)
{
  if (len != mix_buf_len_) {
    SDL_free(mix_buf_);
    mix_buf_ = reinterpret_cast<uint8_t *>(SDL_malloc(len));
    if (mix_buf_ == NULL) {
      SDL_ERROR("SDL_malloc");
      return false;
    }
    mix_buf_len_ = len;
  }
  SDL_memset(mix_buf_, 0, mix_buf_len_);
  return true;
}

int main(int argc, char *argv[])
{
  SmfPlayApp app;
  return app.run(argc, argv);
}
