#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "texture.hpp"
#include <cassert>
#include <SDL.h>
#include <SDL_image.h>
#include "sdl_logger.hpp"

Texture::Texture(SDL_Renderer *renderer_)
  : renderer(renderer_)
  , texture(NULL)
  , filename("")
{
}

Texture::~Texture()
{
  if (texture != NULL) {
    SDL_DestroyTexture(texture);
    texture = NULL;
    LOG_INFO("Texture %p(%s) is destroyed.", this, filename.c_str());
  }
}

bool Texture::load_file(const SP &filename_)
{
  assert(renderer != NULL);
  SDL_Surface *surface = IMG_Load(filename_.c_str());
  if (surface == NULL) {
    LOG_ERROR("IMG_Load() failed: %s", IMG_GetError());
    return false;
  }
  SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
  if (tex == NULL) {
    SDL_ERROR(SDL_CreateTextureFromSurface);
    SDL_FreeSurface(surface);
    return false;
  }
  SDL_FreeSurface(surface);
  texture = tex;
  int w, h;
  if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) == -1) {
    SDL_ERROR(SDL_QueryTexture);
    SDL_DestroyTexture(texture);
    texture = NULL;
    return false;
  }
  width = w;
  height = h;
  filename_.CopyToString(&filename);
  LOG_INFO("Texture %p(%s) loaded.", this, filename.c_str());
  return true;
}
