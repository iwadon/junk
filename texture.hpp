#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED 1

#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST)
#include <boost/cstdint.hpp>
#elif defined(HAVE_STDINT_H)
#include <stdint.h>
#endif
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
