#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator_stream.hpp"
#include "sdl_app.hpp"

class OscillatorSampleApp : public SDLApp
{
public:
  OscillatorSampleApp();
  ~OscillatorSampleApp();
protected:
  bool initialize(int argc, char *argv[]);
  void draw();
  void mix_audio(uint8_t *buf, size_t len);
private:
  OscillatorStream os_;
  uint8_t *mix_buf_;
  size_t mix_buf_len_;
  int y_;
  void draw_wave_form();
};

OscillatorSampleApp::OscillatorSampleApp()
  : SDLApp("oscillator_sample")
  , mix_buf_(NULL)
  , mix_buf_len_(0)
  , y_(height() / 2)
{
  os_.set_sample_rate(48000);
}

OscillatorSampleApp::~OscillatorSampleApp()
{
  free(mix_buf_);
}

bool OscillatorSampleApp::initialize(int /*argc*/, char */*argv*/[])
{
  return true;
}

void OscillatorSampleApp::draw()
{
  SDL_LockAudio();
  draw_wave_form();
  SDL_UnlockAudio();
  draw_strf(0, 0, "mix_buf_len_=%zu", mix_buf_len_);
}

void OscillatorSampleApp::mix_audio(uint8_t *buf, size_t len)
{
  if (len != mix_buf_len_) {
    mix_buf_len_ = len;
    delete mix_buf_;
    mix_buf_ = reinterpret_cast<uint8_t *>(malloc(len));
  }
  os_.set_volume(1.0f);
  os_.read(mix_buf_, mix_buf_len_, 440);
  SDL_MixAudio(buf, mix_buf_, len, SDL_MIX_MAXVOLUME);
}

void OscillatorSampleApp::draw_wave_form()
{
  if (mix_buf_ != NULL) {
    int16_t *buf = reinterpret_cast<int16_t *>(mix_buf_);
    int x_ = 0;
    int y_ = (height() / 2) + buf[0] * (height() / 2) / 32768;
    SDL_SetRenderDrawColor(renderer(), 255, 255, 255, 255);
    for (int x = 1; x < width(); ++x) {
      int y = (height() / 2) + buf[x * (mix_buf_len_ / 2) / width()] * (height() / 2) / 32768;
      SDL_RenderDrawLine(renderer(), x_, y_, x, y);
      x_ = x;
      y_ = y;
    }
  }
}

extern "C"
int main(int argc, char *argv[])
{
  OscillatorSampleApp app;
  return app.run(argc, argv);
}
