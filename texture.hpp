#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED 1

#include "sp.hpp"

struct SDL_Texture;

struct Texture
{
  SDL_Texture *texture;
  std::string filename;
  Texture();
  ~Texture();
  bool load_file(const SP &filename);
};

#endif // !defined(TEXTURE_HPP_INCLUDED)
