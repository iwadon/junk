#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sdl_app.hpp"

class SDLOpenGLSampleApp : public SDLApp
{
public:
  SDLOpenGLSampleApp();
};

SDLOpenGLSampleApp::SDLOpenGLSampleApp()
  : SDLApp("SDL OpenGL Sample")
{
}

int main(int argc, char *argv[])
{
  SDLOpenGLSampleApp app;
  return app.run(argc, argv);
}
