#ifndef SPRITE_HPP_INCLUDED
#define SPRITE_HPP_INCLUDED 1

#ifdef HAVE_SDL_H
#include <SDL.h>
#endif
#include "point.hpp"
#include "sp.hpp"

struct Texture;

struct Sprite
{
  Texture *texture;
  SDL_Rect rect;
  Point pos;
  float rot;
  float scale;
  Sprite();
  bool set_texture(const SP &filename);
  bool set_texture(const SP &filename, const SDL_Rect *rect);
  void draw();
};

#endif // !defined(SPRITE_HPP_INCLUDED)
