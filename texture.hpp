#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED 1

#include <string>
#include <SDL.h>

struct Texture
{
  SDL_Texture *texture;
  std::string filename;
  ~Texture();
  bool load_file(const char *filename);
};

#endif // !defined(TEXTURE_HPP_INCLUDED)
