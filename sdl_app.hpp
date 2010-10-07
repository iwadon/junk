#ifndef SDL_APP_HPP_INCLUDED
#define SDL_APP_HPP_INCLUDED 1

#include <string>
#include <SDL.h>

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
  uint32_t next_ticks_;
  Font *font_;
  bool do_initialize(int argc, char *argv[]);
  void do_finalize();
  void do_move();
  void do_update();
  void do_draw();
  void wait_next_frame();
};

#endif // !defined(SDL_APP_HPP_INCLUDED)
