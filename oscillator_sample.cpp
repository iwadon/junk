#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator_stream.hpp"
#include "sdl_app.hpp"

struct SDLAudioAutoLocker
{
  SDLAudioAutoLocker() { SDL_LockAudio(); }
  ~SDLAudioAutoLocker() { SDL_UnlockAudio(); }
};

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
  int wf_y_;
  void draw_wave_form(int x, int y, int w, int h);
};

OscillatorSampleApp::OscillatorSampleApp()
  : SDLApp("oscillator_sample")
  , mix_buf_(NULL)
  , mix_buf_len_(0)
  , wf_y_(0)
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
  draw_wave_form(0, 0, width(), height());
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

void OscillatorSampleApp::draw_wave_form(int x, int y, int w, int h)
{
  SDLAudioAutoLocker lock;
  if (mix_buf_ == NULL) {
    return;
  }
  const int16_t *buf = reinterpret_cast<const int16_t *>(mix_buf_);
  int x1 = 0;
  wf_y_ = (h / 2) + buf[0] * (h / 2) / 32768;
  SDL_SetRenderDrawColor(renderer(), 255, 255, 255, 255);
  for (int x2 = 1; x2 < w; ++x2) {
    int y2 = (h / 2) + buf[x2 * (mix_buf_len_ / 2) / w] * (h / 2) / 32768;
    SDL_RenderDrawLine(renderer(), x + x1, y + wf_y_, x + x2, y + y2);
    x1 = x2;
    wf_y_ = y2;
  }
}

extern "C"
int main(int argc, char *argv[])
{
  OscillatorSampleApp app;
  return app.run(argc, argv);
}
