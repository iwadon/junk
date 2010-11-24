#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sdl_app.hpp"
#ifdef STDCXX_98_HEADERS
#include <cassert>
#include <ctime>
#include <iostream>
#endif
#ifdef HAVE_SDL_H
#include <SDL.h>
#include <SDL_opengl.h>
#endif
#include "font.hpp"
#include "logger.hpp"

#define SHOW_WINDOW_AFTER_INITIALIZED

static const uint32_t FPS = 60;
static const float FRAME_INTERVAL = 1000.0f / FPS;
static const int MAX_SKIP_FRAMES = 10;
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

SDLApp::SDLApp(const SP &app_name)
  : app_name_(app_name.c_str())
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

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    ERROR("SDL_Init() failed: %s", SDL_GetError());
    return false;
  }

  window_ = SDL_CreateWindow(app_name_.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
			     SDL_WINDOW_OPENGL
#ifndef SHOW_WINDOW_AFTER_INITIALIZED
			     | SDL_WINDOW_SHOWN
#endif
			     );
  if (window_ == NULL) {
    ERROR("SDL_CreateWindow() failed: %s", SDL_GetError());
    return false;
  }
  if (SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTFLIP3 | SDL_RENDERER_PRESENTVSYNC) < 0) {
    ERROR("SDL_CreateRenderer() failed: %s", SDL_GetError());
    return false;
  }

  glcontext_ = SDL_GL_CreateContext(window_);
  if (glcontext_ == NULL) {
    ERROR("SDL_GL_CreateContext() failed: %s", SDL_GetError());
    return false;
  }
  SDL_GL_SetSwapInterval(0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 1);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  SDL_AudioSpec fmt;
  memset(&fmt, 0, sizeof fmt);
  fmt.freq = 48000;
  fmt.format = AUDIO_S16;
  fmt.channels = 2;
  fmt.samples = 512;
  fmt.callback = SDLApp::audio_callback;
  fmt.userdata = this;
  if (SDL_OpenAudio(&fmt, NULL) < 0) {
    ERROR("SDL_OpenAudio() failed: %s", SDL_GetError());
    return false;
  }

  initialize(argc, argv);

  SDL_PauseAudio(0);
  return true;
}

void SDLApp::do_finalize()
{
  SDL_PauseAudio(1);
  finalize();
  SDL_CloseAudio();
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
      controller_.update(event);
    }
  }
  input();
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
  glClear(GL_COLOR_BUFFER_BIT);
  draw();
  {
    char buf[100];
    snprintf(buf, sizeof buf, "%3dfps", fps_.latest_frames);
    draw_string(8, 8, buf);
  }
  SDL_GL_SwapWindow(window_);
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

bool SDLApp::load_font_file(const SP &filename)
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

void SDLApp::audio_callback(void *userdata, Uint8 *stream, int len)
{
  SDLApp *app = reinterpret_cast<SDLApp *>(userdata);
  app->mix_audio(stream, len);
}
