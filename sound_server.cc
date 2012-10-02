#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <SDL.h>
#include <boost/static_assert.hpp>
#include "frame_wait_timer.hpp"
#include "sdl_console_app.hpp"
#include "sdl_logger.hpp"
#include "sound.hpp"

namespace sound_server {

class App : public SDLConsoleApp
{
public:
  App();
  virtual ~App();
protected:
  bool OnInitialize(int argc, char *argv[]);
  void OnFinalize();
  void OnUpdate();
private:
  Sound *sound_;
};

App::App()
  : SDLConsoleApp()
  , sound_(new Sound)
{
}

App::~App()
{
  delete sound_;
}

bool App::OnInitialize(int argc, char *argv[])
{
  int ret = sound_->Initialize();
  if (ret != Sound::RESULT_OK) {
    LOG_ERROR("Sound::initialize() failed");
    return false;
  }
  sound_->StartServer();

  sound_->LoadSndFile("data/sound_data_sample.bin");
  sound_->Play(0);		// XXX

  LOG_INFO("Sound Initialized");
  return true;
}

void App::OnFinalize()
{
  sound_->StopServer();
  sound_->Finalize();
  LOG_INFO("Sound finalized");
}

void App::OnUpdate()
{
  sound_->Update();
}

} // sound_server

int main(int argc, char *argv[])
{
  sound_server::App app;
  return app.Run(argc, argv);
}
