#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sprite.hpp"
#include <SDL.h>
#include <SDL_opengl.h>
#include "sdl_logger.hpp"
#include "texture.hpp"
#include "texture_pool.hpp"

Sprite::Sprite(SDL_Renderer *renderer_)
  : renderer(renderer_)
  , texture(NULL)
{
}

bool Sprite::set_texture(const SP &filename)
{
  return set_texture(filename, NULL);
}

bool Sprite::set_texture(const SP &filename, const SDL_Rect *rect_)
{
  Texture *tex = TexturePool::get_instance().load_file(renderer, filename);
  if (tex == NULL) {
    return false;
  }
  TexturePool::get_instance().destroy(texture);
  texture = tex;
  if (rect_ != NULL) {
    rect = *rect_;
  } else {
    rect.x = 0;
    rect.y = 0;
    rect.w = texture->width;
    rect.h = texture->height;
  }
  return true;
}

void Sprite::draw()
{
  if (texture == NULL || texture->texture == NULL) {
    return;
  }

  SDL_Rect dst;
  dst.x = 0;
  dst.y = 0;
  dst.w = texture->width;
  dst.h = texture->height;

  glPushMatrix();
  glTranslatef(pos.x, pos.y, 0.0f);
  glRotatef(rot, 0.0f, 0.0f, 1.0f);
  glTranslatef(-(texture->width * scale / 2.0f), -(texture->height * scale / 2.0f), 0.0f);
  glScalef(scale, scale, 1.0f);
  if (SDL_RenderCopy(renderer, texture->texture, &rect, &dst) == -1) {
    SDL_ERROR(SDL_RenderCopy);
  }
  glPopMatrix();
}
