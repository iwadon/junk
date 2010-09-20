#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "texture.hpp"
#include <iostream>
#include <SDL_image.h>

Texture::~Texture()
{
  SDL_DestroyTexture(texture);
  texture = NULL;
}

bool Texture::load_file(const char *filename_)
{
  SDL_Surface *surface = IMG_Load(filename_);
  if (surface == NULL) {
    std::cerr << "IMG_Load: " << IMG_GetError() << std::endl;
    return false;
  }
  SDL_Texture *tex = SDL_CreateTextureFromSurface(0, surface);
  if (tex == NULL) {
    std::cerr << "can not create texture: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(surface);
    return false;
  }
  SDL_FreeSurface(surface);
  texture = tex;
  filename = filename_;
  return true;
}
