#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sdl_console_app.hpp"
#include "sdl_logger.hpp"

namespace {

volatile sig_atomic_t quit = 0;

void sigint_handler(int sig)
{
  quit = 1;
}

}

SDLConsoleApp::SDLConsoleApp()
  : fwt_(60, 2)
{
  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    perror("signal() failed");
  }
}

SDLConsoleApp::~SDLConsoleApp()
{
}

int SDLConsoleApp::Run(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    SDL_ERROR(SDL_Init);
    return 1;
  }

  if (!OnInitialize(argc, argv)) {
    return 1;
  }

  fwt_.reset();
  while (!quit) {
    OnUpdate();
    fwt_.wait();
  }

  OnFinalize();

  SDL_Quit();

  return 0;
}

void SDLConsoleApp::QuitMainLoop()
{
  quit = 1;
}
