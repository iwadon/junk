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
};

OscillatorSampleApp::OscillatorSampleApp()
  : SDLApp("oscillator_sample")
  , mix_buf_(NULL)
  , mix_buf_len_(0)
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

extern "C"
int main(int argc, char *argv[])
{
  OscillatorSampleApp app;
  return app.run(argc, argv);
}
