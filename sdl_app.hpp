#ifndef SDL_APP_HPP_INCLUDED
#define SDL_APP_HPP_INCLUDED 1

#include <string>
#include "fps.hpp"
#include "logger.hpp"

#ifdef USE_OPENGL
#ifdef HAVE_SDL_H
#include <SDL.h>
#endif
#endif

struct SDL_Window;
class Font;

class SDLApp
{
public:
  SDLApp(const std::string &app_name);
  virtual ~SDLApp();
  int run(int argc, char *argv[]);
protected:
  virtual bool initialize(int /*argc*/, char */*argv*/[]) { return true; }
  virtual void finalize() {}
  virtual void input() {}
  virtual void move() {}
  virtual void update() {}
  virtual void draw() {}
  void set_bg_color(const uint32_t rgba);
  bool load_font_file(const char *filename);
  void draw_chr(int x, int y, int chr);
  void draw_string(int x, int y, const char *str);
private:
  std::string app_name_;
  SDL_Window *window_;
  bool done_;
  uint8_t bg_color_[4];
  float prev_ticks_;
  int frames_;
  Font *font_;
  FPS fps_;
#ifdef USE_OPENGL
  SDL_GLContext glcontext_;
#endif
  bool do_initialize(int argc, char *argv[]);
  void do_finalize();
  void do_input();
  void do_move();
  void do_update();
  void do_draw();
  int calculate_frames();
protected:
  Logger logger_;
};

#endif // !defined(SDL_APP_HPP_INCLUDED)
