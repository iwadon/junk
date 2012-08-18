#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED 1

#include <boost/cstdint.hpp>
#include "sp.hpp"

struct SDL_Renderer;
struct SDL_Texture;

struct Texture
{
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  uint32_t width;
  uint32_t height;
  std::string filename;
  Texture(SDL_Renderer *renderer);
  ~Texture();
  bool load_file(const SP &filename);
};

#endif // !defined(TEXTURE_HPP_INCLUDED)
