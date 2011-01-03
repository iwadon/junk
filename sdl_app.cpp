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
  , frame_wait_timer_(FPS, MAX_SKIP_FRAMES)
  , prev_mod_(KMOD_NONE)
{
  set_bg_color(0x00a000ff);
}

SDLApp::~SDLApp()
{
  do_finalize();
  delete font_;
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

  frame_wait_timer_.reset();
  done_ = false;
  while (!done_) {
    frames_ = frame_wait_timer_.wait();
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
    SDL_ERROR("SDL_Init");
    return false;
  }

  window_ = SDL_CreateWindow(app_name_.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
			     SDL_WINDOW_OPENGL
#ifndef SHOW_WINDOW_AFTER_INITIALIZED
			     | SDL_WINDOW_SHOWN
#endif
			     );
  if (window_ == NULL) {
    SDL_ERROR("SDL_CreateWindow");
    return false;
  }
  if (SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTFLIP3 | SDL_RENDERER_PRESENTVSYNC) < 0) {
    SDL_ERROR("SDL_CreateRenderer");
    return false;
  }

  glcontext_ = SDL_GL_CreateContext(window_);
  if (glcontext_ == NULL) {
    SDL_ERROR("SDL_GL_CreateContext");
    return false;
  }
  SDL_GL_SetSwapInterval(0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 1);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  SDL_AudioSpec spec;
  memset(&spec, 0, sizeof spec);
  spec.freq = 48000;
  spec.format = AUDIO_S16MSB;
  spec.channels = 1;
  spec.samples = 512;
  spec.callback = SDLApp::audio_callback;
  spec.userdata = this;
  if (SDL_OpenAudio(&spec, &audio_spec_) < 0) {
    SDL_ERROR("SDL_OpenAudio");
    return false;
  }

  INFO("Audio Drivers:");
  int num_audio_drivers = SDL_GetNumAudioDrivers();
  const char *current_audio_driver = SDL_GetCurrentAudioDriver();
  for (int i = 0; i < num_audio_drivers; ++i) {
    const char *audio_driver = SDL_GetAudioDriver(i);
    INFO("  %d: %s%s", i, audio_driver, !strcmp(audio_driver, current_audio_driver) ? " (current)" : "");
  }

  INFO("Audio Spec:");
  INFO("  freq: %d", audio_spec_.freq);
  INFO("  format: %u (%s, %s, %s, %ubit)", audio_spec_.format,
       SDL_AUDIO_ISSIGNED(audio_spec_.format) ? "signed" : "unsigned",
       SDL_AUDIO_ISBIGENDIAN(audio_spec_.format) ? "big-endian" : "little-endian",
       SDL_AUDIO_ISFLOAT(audio_spec_.format) ? "float" : "integer",
       SDL_AUDIO_BITSIZE(audio_spec_.format));
  INFO("  channels: %u", audio_spec_.channels);
  INFO("  silence: %u", audio_spec_.silence);
  INFO("  samples: %u", audio_spec_.samples);
  INFO("  padding: %u", audio_spec_.padding);
  INFO("  size: %u", audio_spec_.size);
  
  initialize(argc, argv);

  SDL_PauseAudio(0);
  return true;
}

void SDLApp::do_finalize()
{
  SDL_PauseAudio(1);
  finalize();
  SDL_CloseAudio();

  SDL_GL_DeleteContext(glcontext_);
  glcontext_ = NULL;
  INFO("Deleted an OpenGL context.");
  SDL_DestroyRenderer(window_);
  INFO("Destroy the rendering context.");
  SDL_DestroyWindow(window_);
  window_ = NULL;
  INFO("Destroy a window.");

  SDL_Quit();
  INFO("Quit SDL system.");
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
      set_fps();
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
    draw_str(8, 8, buf);
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

void SDLApp::set_fps()
{
  SDLMod mod = SDL_GetModState();
  SDLMod on_mod = static_cast<SDLMod>(mod & ~prev_mod_);
  if (on_mod & KMOD_CTRL) {
    frame_wait_timer_.set_fps(FPS * 2);
  } else if (mod & KMOD_SHIFT) {
    frame_wait_timer_.set_fps(FPS / 10);
  } else {
    frame_wait_timer_.set_fps(FPS);
  }
  prev_mod_ = mod;
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

void SDLApp::draw_str(int x, int y, const char *str)
{
  assert(font_ != NULL);
  font_->draw_str(x, y, str);
}

void SDLApp::draw_strf(int x, int y, const char *format, ...)
{
  assert(font_ != NULL);
  va_list args;
  va_start(args, format);
  font_->draw_strfv(x, y, format, args);
  va_end(args);
}

/**
 * @param [in]    userdata 任意のデータへのポインタ。ここではSDLAppクラスへのポインタが渡されている。
 * @param [inout] stream   オーディオの出力データを格納するメモリの先頭アドレス。
 * @param [in]    len      streamが指すメモリの大きさ。バイト単位。サンプル単位ではないことに注意すること。
 */
void SDLApp::audio_callback(void *userdata, Uint8 *stream, int len)
{
  SDLApp *app = reinterpret_cast<SDLApp *>(userdata);
  app->mix_audio(stream, len);
}
