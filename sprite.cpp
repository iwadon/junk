#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sprite.hpp"
#include "texture_pool.hpp"

Sprite::Sprite()
  : texture(NULL)
{
}

bool Sprite::load_texture_file(const SP &filename)
{
  Texture *tex = TexturePool::get_instance().load_file(filename);
  if (tex == NULL) {
    return false;
  }
  TexturePool::get_instance().destroy(texture);
  texture = tex;
  return true;
}
