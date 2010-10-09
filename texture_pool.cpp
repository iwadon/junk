#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "texture_pool.hpp"
#ifdef STDCXX_98_HEADERS
#include <cassert>
#endif

TexturePool &TexturePool::get_instance()
{
  static TexturePool instance;
  return instance;
}

Texture *TexturePool::load_file(const char *filename)
{
  Texture *tex;
  texture_map_type::iterator i = texture_map_.find(filename);
  if (i != texture_map_.end()) {
    tex = (*i).second;
  } else {
    tex = texture_pool_.construct();
    if (!tex->load_file(filename)) {
      return NULL;
    }
    texture_map_[filename] = tex;
  }
  return tex;
}

void TexturePool::destroy(Texture *tex)
{
  assert(tex != NULL);
  texture_map_.erase(tex->filename.c_str());
  texture_pool_.destroy(tex);
}
