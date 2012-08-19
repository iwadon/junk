#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sdl_app.hpp"
#ifdef STDCXX_98_HEADERS
#include <cassert>
#include <ctime>
#include <iostream>
#endif
#include <SDL.h>
#ifdef ENABLE_OPENGL
#include <SDL_opengl.h>
#endif
#include "font.hpp"
#include "sdl_logger.hpp"

#define SHOW_WINDOW_AFTER_INITIALIZED

static const uint32_t FPS = 60;
static const float FRAME_INTERVAL = 1000.0f / FPS;
static const int MAX_SKIP_FRAMES = 10;
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

enum {
  LOAD_TIME_INPUT,
  LOAD_TIME_MOVE,
  LOAD_TIME_UPDATE,
  LOAD_TIME_DRAW,
};

SDLApp::SDLApp(const SP &app_name)
  : app_name_(app_name.c_str())
  , frame_wait_timer_(FPS, MAX_SKIP_FRAMES)
  , prev_mod_(KMOD_NONE)
{
  set_bg_color(0x00a000ff);
  load_time_.set_color(LOAD_TIME_INPUT, 0xff, 0x00, 0x00, 0xc0);
  load_time_.set_name(LOAD_TIME_INPUT, "Input");
  load_time_.activate(LOAD_TIME_INPUT);
  load_time_.set_color(LOAD_TIME_MOVE, 0xff, 0xff, 0x00, 0xc0);
  load_time_.set_name(LOAD_TIME_MOVE, "Move");
  load_time_.activate(LOAD_TIME_MOVE);
  load_time_.set_color(LOAD_TIME_UPDATE, 0xff, 0x00, 0xff, 0xc0);
  load_time_.set_name(LOAD_TIME_UPDATE, "Update");
  load_time_.activate(LOAD_TIME_UPDATE);
  load_time_.set_color(LOAD_TIME_DRAW, 0x00, 0xff, 0x00, 0xc0);
  load_time_.set_name(LOAD_TIME_DRAW, "Draw");
  load_time_.activate(LOAD_TIME_DRAW);
}

SDLApp::~SDLApp()
{
  do_finalize();
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
      load_time_.start(LOAD_TIME_INPUT);
      do_input();
      load_time_.stop(LOAD_TIME_INPUT);
      load_time_.start(LOAD_TIME_MOVE);
      do_move();
      load_time_.stop(LOAD_TIME_MOVE);
      load_time_.start(LOAD_TIME_UPDATE);
      do_update();
      load_time_.stop(LOAD_TIME_UPDATE);
      fps_.update();
    }
    load_time_.start(LOAD_TIME_DRAW);
    do_draw();
    load_time_.stop(LOAD_TIME_DRAW);
    load_time_.flip();
  }
  return 0;
}

bool SDLApp::do_initialize(int argc, char *argv[])
{
  srand(time(NULL));

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    SDL_ERROR(SDL_Init);
    return false;
  }

  window_ = SDL_CreateWindow(app_name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
  if (window_ == NULL) {
    SDL_ERROR(SDL_CreateWindow);
    return false;
  }
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
  if (renderer_ == NULL) {
    SDL_ERROR(SDL_CreateRenderer);
    return false;
  }

#ifdef ENABLE_OPENGL
  glcontext_ = SDL_GL_CreateContext(window_);
  if (glcontext_ == NULL) {
    SDL_ERROR("SDL_GL_CreateContext");
    return false;
  }
  SDL_GL_SetSwapInterval(0);
  LOG_INFO("Created an OpenGL context.");

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 1);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  LOG_INFO("Initialized OpenGL.");
#endif

#ifdef SDLAPP_ENABLE_AUDIO
  SDL_AudioSpec spec;
  memset(&spec, 0, sizeof spec);
  spec.freq = 48000;
  spec.format = AUDIO_S16MSB;
  spec.channels = 1;
  spec.samples = 512;
  spec.callback = SDLApp::audio_callback;
  spec.userdata = this;
  if (SDL_OpenAudio(&spec, &audio_spec_) < 0) {
    SDL_ERROR(SDL_OpenAudio);
    return false;
  }

  LOG_INFO("Audio Drivers:");
  int num_audio_drivers = SDL_GetNumAudioDrivers();
  const char *current_audio_driver = SDL_GetCurrentAudioDriver();
  for (int i = 0; i < num_audio_drivers; ++i) {
    const char *audio_driver = SDL_GetAudioDriver(i);
    LOG_INFO("  %d: %s%s", i, audio_driver, !strcmp(audio_driver, current_audio_driver) ? " (current)" : "");
  }

  LOG_INFO("Audio Spec:");
  LOG_INFO("  freq: %d", audio_spec_.freq);
  LOG_INFO("  format: %u (%s, %s, %s, %ubit)", audio_spec_.format,
       SDL_AUDIO_ISSIGNED(audio_spec_.format) ? "signed" : "unsigned",
       SDL_AUDIO_ISBIGENDIAN(audio_spec_.format) ? "big-endian" : "little-endian",
       SDL_AUDIO_ISFLOAT(audio_spec_.format) ? "float" : "integer",
       SDL_AUDIO_BITSIZE(audio_spec_.format));
  LOG_INFO("  channels: %u", audio_spec_.channels);
  LOG_INFO("  silence: %u", audio_spec_.silence);
  LOG_INFO("  samples: %u", audio_spec_.samples);
  LOG_INFO("  padding: %u", audio_spec_.padding);
  LOG_INFO("  size: %u", audio_spec_.size);
#endif // defined(SDLAPP_ENABLE_AUDIO)

  font_ = new Font(renderer_);
  if (!load_font_file("data/font5x5.png")) {
    return false;
  }
  
  initialize(argc, argv);

#ifdef SDLAPP_ENABLE_AUDIO
  SDL_PauseAudio(0);
#endif

  return true;
}

void SDLApp::do_finalize()
{
#ifdef SDLAPP_ENABLE_AUDIO
  SDL_PauseAudio(1);
#endif
  finalize();
#ifdef SDLAPP_ENABLE_AUDIO
  SDL_CloseAudio();
#endif

  delete font_;
  font_ = NULL;

#ifdef ENABLE_OPENGL
  SDL_GL_DeleteContext(glcontext_);
  glcontext_ = NULL;
  LOG_INFO("Deleted an OpenGL context.");
#endif
  SDL_DestroyRenderer(renderer_);
  LOG_INFO("Destroy the rendering context.");
  renderer_ = NULL;
  SDL_DestroyWindow(window_);
  window_ = NULL;
  LOG_INFO("Destroy a window.");

  SDL_Quit();
  LOG_INFO("Quit SDL system.");
}

void SDLApp::do_input()
{
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT ||
	(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) ||
	(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q && (event.key.keysym.mod == KMOD_LGUI || event.key.keysym.mod == KMOD_RGUI))) {
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
  SDL_SetRenderDrawColor(renderer_, bg_color_[0], bg_color_[1], bg_color_[2], bg_color_[3]);
  SDL_RenderClear(renderer_);
  draw();
  font_->draw_strf(8, 8, "%3dfps", fps_.latest_frames);
  load_time_.draw(font_, 0, 80);
  SDL_RenderPresent(renderer_);
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
  SDL_Keymod mod = SDL_GetModState();
  SDL_Keymod on_mod = static_cast<SDL_Keymod>(mod & ~prev_mod_);
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

#ifdef SDLAPP_ENABLE_AUDIO
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
#endif
