#ifndef SPRITE_HPP_INCLUDED
#define SPRITE_HPP_INCLUDED 1

#include <SDL.h>
#include "point_2d.hpp"
#include "sp.hpp"

struct Texture;

struct Sprite
{
  Texture *texture;
  SDL_Rect rect;
  Point2D pos;
  float rot;
  float scale;
  Sprite();
  bool set_texture(const SP &filename);
  bool set_texture(const SP &filename, const SDL_Rect *rect);
  void draw();
};

#endif // !defined(SPRITE_HPP_INCLUDED)
