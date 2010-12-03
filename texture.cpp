#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "texture.hpp"
#ifdef HAVE_SDL_H
#include <SDL.h>
#endif
#ifdef HAVE_SDL_IMAGE_H
#include <SDL_image.h>
#endif
#include "logger.hpp"

Texture::Texture()
  : texture(NULL)
  , filename("")
{
}

Texture::~Texture()
{
  if (texture != NULL) {
    SDL_DestroyTexture(texture);
    texture = NULL;
    INFO("Texture %p(%s) is destroyed.", this, filename.c_str());
  }
}

bool Texture::load_file(const SP &filename_)
{
  SDL_Surface *surface = IMG_Load(filename_.c_str());
  if (surface == NULL) {
    ERROR("IMG_Load() failed: %s", IMG_GetError());
    return false;
  }
  SDL_Texture *tex = SDL_CreateTextureFromSurface(0, surface);
  if (tex == NULL) {
    SDL_ERROR("SDL_CreateTextureFromSurface");
    SDL_FreeSurface(surface);
    return false;
  }
  SDL_FreeSurface(surface);
  texture = tex;
  int w, h;
  if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) == -1) {
    SDL_ERROR("SDL_QueryTexture");
    SDL_DestroyTexture(texture);
    texture = NULL;
    return false;
  }
  width = w;
  height = h;
  filename_.CopyToString(&filename);
  INFO("Texture %p(%s) loaded.", this, filename.c_str());
  return true;
}
