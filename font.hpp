#ifndef FONT_HPP_INCLUDED
#define FONT_HPP_INCLUDED 1

#include "texture.hpp"

class Font
{
public:
  ~Font();
  bool load_file(const char *filename);
  void draw_chr(const int x, const int y, const int chr);
  void draw_str(const int x, const int y, const char *str);
  void draw_strf(const int x, const int y, const char *format, ...);
private:
  Texture *tex_;
};

#endif // !defined(FONT_HPP_INCLUDED)
