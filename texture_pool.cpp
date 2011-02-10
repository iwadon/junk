#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "texture_pool.hpp"
#ifdef STDCXX_98_HEADERS
#include <cassert>
#endif
#include "texture.hpp"

TexturePool &TexturePool::get_instance()
{
  static TexturePool instance;
  return instance;
}

Texture *TexturePool::load_file(SDL_Renderer *renderer, const SP &filename)
{
  Texture *tex;
  texture_map_type::iterator i = texture_map_.find(filename.c_str());
  if (i != texture_map_.end()) {
    tex = (*i).second;
  } else {
    tex = texture_pool_.construct(renderer);
    if (!tex->load_file(filename)) {
      return NULL;
    }
    texture_map_[tex->filename] = tex;
  }
  return tex;
}

void TexturePool::destroy(Texture *tex)
{
  if (tex != NULL) {
    texture_map_type::iterator i = texture_map_.find(tex->filename);
    if (i != texture_map_.end()) {
      texture_map_.erase(i);
    }
    assert(texture_map_.find(tex->filename) == texture_map_.end());
    texture_pool_.destroy(tex);
  }
}
