#ifndef SDL_APP_HPP_INCLUDED
#define SDL_APP_HPP_INCLUDED 1

#include <string>
#include <SDL.h>
#include "fps.hpp"
#include "frame_wait_timer.hpp"
#include "load_time.hpp"
#include "pad.hpp"
#include "sp.hpp"

#define SDLAPP_ENABLE_AUDIO

struct SDL_Window;
class Font;

class SDLApp
{
public:
  SDLApp(const SP &app_name);
  virtual ~SDLApp();
  int run(int argc, char *argv[]);
  PadBase *pad() { return pad_; }
  SDL_Renderer *renderer() { return renderer_; }
  int width() const;
  int height() const;
protected:
  virtual bool initialize(int /*argc*/, char */*argv*/[]) { return true; }
  virtual void finalize() {}
  virtual void input() {}
  virtual void move() {}
  virtual void update() {}
  virtual void draw() {}
#ifdef SDLAPP_ENABLE_AUDIO
  virtual void mix_audio(uint8_t *buf, size_t len);
#endif
  void set_bg_color(const uint32_t rgba);
  bool load_font_file(const SP &filename);
  void draw_chr(int x, int y, int chr);
  void draw_str(int x, int y, const char *str);
  void draw_strf(int x, int y, const char *format, ...);
private:
  std::string app_name_;
  SDL_Window *window_;
  SDL_Renderer *renderer_;
  bool done_;
  uint8_t bg_color_[4];
  float prev_ticks_;
  int frames_;
  Font *font_;
  FPS fps_;
  SDL_GLContext glcontext_;
#ifdef SDLAPP_ENABLE_AUDIO
  SDL_AudioSpec audio_spec_;
#endif
  FrameWaitTimer frame_wait_timer_;
  SDL_Keymod prev_mod_;
  LoadTime load_time_;
  PadBase *pad_;
  bool do_initialize(int argc, char *argv[]);
  void do_finalize();
  void do_input();
  void do_move();
  void do_update();
  void do_draw();
  void set_fps();
#ifdef SDLAPP_ENABLE_AUDIO
  static void audio_callback(void *userdata, Uint8 *stream, int len);
#endif
};

#endif // !defined(SDL_APP_HPP_INCLUDED)
