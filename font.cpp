#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cassert>
#include <cstdarg>
#include <iostream>
#include <SDL.h>
#include "font.hpp"
#include "texture_pool.hpp"

Font::~Font()
{
  if (tex_ != NULL) {
    TexturePool::get_instance().destroy(tex_);
  }
}

bool Font::load_file(const char *filename)
{
  assert(filename != NULL);
  tex_ = TexturePool::get_instance().load_file(filename);
  return tex_ != NULL;
}

void Font::draw_chr(const int x, const int y, const int chr)
{
  assert(tex_ != NULL);
  SDL_Rect srcrect;
  unsigned char c = chr;
  srcrect.x = 8 * (c & 0xf);
  srcrect.y = 8 * ((c & 0xf0) >> 4);
  srcrect.w = 8;
  srcrect.h = 8;
  static SDL_Rect dstrect;
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = 8;
  dstrect.h = 8;
  int result;
  result = SDL_RenderCopy(tex_->texture, &srcrect, &dstrect);
  if (result != 0) {
    std::cerr << "SDL_RenderCopy: " << SDL_GetError() << std::endl;
  }
}

void Font::draw_str(const int x, const int y, const char *str)
{
  assert(str != NULL);
  int x_ = x;
  int y_ = y;
  for (const char *p = str; *p != '\0'; ++p) {
    draw_chr(x_, y_, *p);
    x_ += 8;
  }
}

void Font::draw_strf(const int x, const int y, const char *format, ...)
{
  char buf[256];
  va_list args;
  va_start(args, format);
  vsnprintf(buf, sizeof buf, format, args);
  va_end(args);
  draw_str(x, y, buf);
}
