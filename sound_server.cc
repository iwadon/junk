#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <SDL.h>
#include <boost/static_assert.hpp>
#include "frame_wait_timer.hpp"
#include "sdl_logger.hpp"
#include "sound.hpp"

namespace sound_server {

volatile sig_atomic_t quit = 0;

void sigint_handler(int sig)
{
  quit = 1;
}

class App
{
public:
  App();
  ~App();
  int run(int argc, char *argv[]);
protected:
  bool initialize(int argc, char *argv[]);
  void finalize();
private:
  Sound *sound_;
  FrameWaitTimer fwt_;
};

App::App()
  : sound_(new Sound)
  , fwt_(60, 2)
{
  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    perror("signal() failed");
  }
}

App::~App()
{
  finalize();
  delete sound_;
}

int App::run(int argc, char *argv[])
{
  if (!initialize(argc, argv)) {
    return 1;
  }

  fwt_.reset();
  while (!quit) {
    sound_->Update();
    fwt_.wait();
  }

  return 0;
}

bool App::initialize(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    SDL_ERROR(SDL_Init);
    return 1;
  }

  int ret = sound_->Initialize();
  if (ret != Sound::RESULT_OK) {
    LOG_ERROR("Sound::initialize() failed");
    return false;
  }
  sound_->Play(0);		// XXX

  LOG_INFO("Sound Initialized");
  return true;
}

void App::finalize()
{
  sound_->StopServer();
  sound_->Finalize();
  LOG_INFO("Sound finalized");

  SDL_Quit();
}

} // sound_server

int main(int argc, char *argv[])
{
  sound_server::App app;
  return app.run(argc, argv);
}
