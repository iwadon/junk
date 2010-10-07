#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sdl_app.hpp"
#include <cassert>
#include <iostream>
#include <ctime>
#include "font.hpp"

#define SHOW_WINDOW_AFTER_INITIALIZED

static const uint32_t FPS_TICKS = 1000 / 60;

SDLApp::SDLApp(const std::string &app_name)
  : app_name_(app_name)
  , next_ticks_(SDL_GetTicks() + FPS_TICKS)
  , font_(new Font)
{
  set_bg_color(0x00a000ff);
}

SDLApp::~SDLApp()
{
  finalize();
}

int SDLApp::run(int argc, char *argv[])
{
  if (!do_initialize(argc, argv)) {
    return 1;
  }
#ifdef SHOW_WINDOW_AFTER_INITIALIZED
  do_draw();
  SDL_ShowWindow(window_);
#endif

  done_ = false;
  while (!done_) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
	done_ = true;
	break;
      case SDL_WINDOWEVENT:
	switch (event.window.event) {
	case SDL_WINDOWEVENT_CLOSE:
	  done_ = true;
	  break;
	}
	break;
      case SDL_KEYDOWN:
	if (event.key.keysym.sym == SDLK_q && (event.key.keysym.mod == KMOD_LGUI || event.key.keysym.mod == KMOD_RGUI)) {
	  done_ = true;
	}
	break;
      }
    }
    do_move();
    do_update();
    do_draw();
    wait_next_frame();
  }
  return 0;
}

bool SDLApp::do_initialize(int argc, char *argv[])
{
  srand(time(NULL));

  window_ = SDL_CreateWindow(app_name_.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
#ifdef SHOW_WINDOW_AFTER_INITIALIZED
			     0
#else
			     SDL_WINDOW_SHOWN
#endif
			     );
  if (window_ == NULL) {
    std::cerr << "ERROR: SDL_CreateWindow: " << SDL_GetError() << std::endl;
    return false;
  }
  if (SDL_CreateRenderer(window_, -1, 0/*SDL_RENDERER_PRESENTFLIP3*/) < 0) {
    std::cerr << "ERROR: SDL_CreateRenderer: " << SDL_GetError() << std::endl;
    return false;
  }

  initialize(argc, argv);

  return true;
}

void SDLApp::do_finalize()
{
  finalize();
  SDL_Quit();
}

void SDLApp::do_move()
{
  move();
}

void SDLApp::do_update()
{
  update();
}

void SDLApp::do_draw()
{
  int result;

  result = SDL_SetRenderDrawColor(bg_color_[0], bg_color_[1], bg_color_[2], bg_color_[3]);
  assert(result == 0);
  result = SDL_RenderClear();
  assert(result == 0);
  draw();
  SDL_RenderPresent();
}

void SDLApp::set_bg_color(const uint32_t rgba)
{
  bg_color_[0] = (rgba & 0xff000000) >> 24;
  bg_color_[1] = (rgba & 0x00ff0000) >> 16;
  bg_color_[2] = (rgba & 0x0000ff00) >>  8;
  bg_color_[3] = (rgba & 0x000000ff) >>  0;
}

void SDLApp::wait_next_frame()
{
  uint32_t now;
  while (true) {
    now = SDL_GetTicks();
    if (now > next_ticks_) {
      break;
    }
    SDL_Delay(1);
  }
  next_ticks_ += FPS_TICKS;
}

bool SDLApp::load_font_file(const char *filename)
{
  assert(font_ != NULL);
  return font_->load_file(filename);
}

void SDLApp::draw_chr(int x, int y, int chr)
{
  assert(font_ != NULL);
  font_->draw_chr(x, y, chr);
}

void SDLApp::draw_string(int x, int y, const char *str)
{
  assert(font_ != NULL);
  font_->draw_str(x, y, str);
}
