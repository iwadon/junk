#ifndef SDL_CONSOLE_APP_HPP_INCLUDED
#define SDL_CONSOLE_APP_HPP_INCLUDED 1

#include "frame_wait_timer.hpp"

class SDLConsoleApp
{
public:
  SDLConsoleApp();
  virtual ~SDLConsoleApp();
  virtual int Run(int argc, char *argv[]);
protected:
  virtual bool OnInitialize(int argc, char *argv[]) = 0;
  virtual void OnFinalize() = 0;
  virtual void OnUpdate() = 0;
private:
  FrameWaitTimer fwt_;
};

#endif // !defined(SDL_CONSOLE_APP_HPP_INCLUDED)
