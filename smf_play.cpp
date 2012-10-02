#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef STDCXX_98_HEADERS
#include <cstddef>
#include <iostream>
#endif
#include <SDL.h>
#include "frame_wait_timer.hpp"
#include "instrument.hpp"
#include "sdl_logger.hpp"
#include "song.hpp"

class App
{
public:
  App();
  ~App();
  int run(int argc, char *argv[]);
  bool initialize(int argc, char *argv[]);
  void update();
  void mix_audio(uint8_t *buf, size_t len);
private:
  Song song_;
  Instrument inst_;
  FrameWaitTimer fwt_;
  SDL_AudioSpec audio_spec_;
  static void sdl_audio_callback(void *userdata, Uint8 *stream, int len);
};

App::App()
  : fwt_(60, 10)
{
}

App::~App()
{
  SDL_PauseAudio(1);
  SDL_CloseAudio();
  SDL_Quit();
}

int App::run(int argc, char *argv[])
{
  if (argc != 2) {
    return 1;
  }

  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    SDL_ERROR(SDL_Init);
    return 1;
  }

  SDL_AudioSpec spec;
  memset(&spec, 0, sizeof spec);
  spec.freq = 48000;
  spec.format = AUDIO_S16LSB;
  spec.channels = 1;
  spec.samples = 512;
  spec.callback = App::sdl_audio_callback;
  spec.userdata = this;
  if (SDL_OpenAudio(&spec, &audio_spec_) < 0) {
    SDL_ERROR(SDL_OpenAudio);
    return false;
  }
  SDL_PauseAudio(0);

  song_.set_instrument(&inst_);
  song_.load_file(argv[1]);
  song_.play();
  fwt_.reset();
  bool done = false;
  while (!done) {
    int frames = fwt_.wait();
    for (int i = 0; i < frames; ++i) {
      song_.update();
      if (!song_.is_playing()) {
	done = true;
	break;
      }
    }
  }
  return 0;
}

void App::sdl_audio_callback(void *userdata, Uint8 *stream, int len)
{
  App *app = reinterpret_cast<App *>(userdata);
  memset(stream, 0, len);
  app->song_.mix_audio(stream, len);
}

int main(int argc, char *argv[])
{
  App app;
  return app.run(argc, argv);
}
