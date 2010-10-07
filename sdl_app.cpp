#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sdl_app.hpp"
#include <cassert>
#include <iostream>
#include <ctime>
#include "font.hpp"

#define SHOW_WINDOW_AFTER_INITIALIZED

static const uint32_t FPS = 60;
static const float FRAME_INTERVAL = 1000.0f / FPS;
static const int MAX_SKIP_FRAMES = 10;

SDLApp::SDLApp(const std::string &app_name)
  : app_name_(app_name)
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

  prev_ticks_ = SDL_GetTicks();
  done_ = false;
  while (!done_) {
    frames_ = calculate_frames();
    for (int i = 0; i < frames_; ++i) {
      do_input();
      do_move();
      do_update();
      fps_.update();
    }
    do_draw();
  }
  return 0;
}

bool SDLApp::do_initialize(int argc, char *argv[])
{
  srand(time(NULL));

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "ERROR: SDL_Init: " << SDL_GetError() << std::endl;
    return false;
  }

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
  if (SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTFLIP3/* | SDL_RENDERER_PRESENTVSYNC*/) < 0) {
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

void SDLApp::do_input()
{
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT ||
	event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE ||
	event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q && (event.key.keysym.mod == KMOD_LGUI || event.key.keysym.mod == KMOD_RGUI)) {
      done_ = true;
    } else {
      input();
    }
  }
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
  {
    char buf[100];
    snprintf(buf, sizeof buf, "%3dfps", fps_.latest_frames);
    draw_string(8, 8, buf);
  }
  SDL_RenderPresent();
}

void SDLApp::set_bg_color(const uint32_t rgba)
{
  bg_color_[0] = (rgba & 0xff000000) >> 24;
  bg_color_[1] = (rgba & 0x00ff0000) >> 16;
  bg_color_[2] = (rgba & 0x0000ff00) >>  8;
  bg_color_[3] = (rgba & 0x000000ff) >>  0;
}

static inline float get_frame_interval()
{
  SDLMod mod = SDL_GetModState();
  if (mod & KMOD_CTRL) {
    return FRAME_INTERVAL / 2;
  } else if (mod & KMOD_SHIFT) {
    return FRAME_INTERVAL * 10;
  } else {
    return FRAME_INTERVAL;
  }
}

int SDLApp::calculate_frames()
{
  float ticks = SDL_GetTicks();
  float interval = get_frame_interval();
  int frames = static_cast<int>((ticks - prev_ticks_) / interval);
  if (frames <= 0) {
    frames = 1;
    SDL_Delay(static_cast<Uint32>(prev_ticks_ + interval - ticks));
    prev_ticks_ += interval;
  } else {
    if (frames > MAX_SKIP_FRAMES) {
      frames = MAX_SKIP_FRAMES;
    }
    prev_ticks_ = ticks;
  }
  return frames;
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
