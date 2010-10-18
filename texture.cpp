#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "texture.hpp"
#ifdef STDCXX_98_HEADERS
#include <iostream>
#endif
#ifdef HAVE_SDL_H
#include <SDL.h>
#endif
#ifdef HAVE_SDL_IMAGE_H
#include <SDL_image.h>
#endif
#include "logger.hpp"

Texture::~Texture()
{
  if (texture != NULL) {
    SDL_DestroyTexture(texture);
    texture = NULL;
    glogger.info("Texture is destroyed: %s", filename.c_str());
  }
}

bool Texture::load_file(const char *filename_)
{
  SDL_Surface *surface = IMG_Load(filename_);
  if (surface == NULL) {
    glogger.error("IMG_Load() failed: %s", IMG_GetError());
    return false;
  }
  SDL_Texture *tex = SDL_CreateTextureFromSurface(0, surface);
  if (tex == NULL) {
    glogger.error("SDL_CreateTextureFromSurface() failed: %s", SDL_GetError());
    SDL_FreeSurface(surface);
    return false;
  }
  SDL_FreeSurface(surface);
  texture = tex;
  filename = filename_;
  glogger.info("Texture is loaded: %s", filename.c_str());
  return true;
}
