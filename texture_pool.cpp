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
  texture_map_type::iterator i = find(filename);
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
  texture_map_type::iterator i = find(tex->filename.c_str());
  if (i != texture_map_.end()) {
    texture_map_.erase(i);
  }
  assert(texture_map_.find(tex->filename.c_str()) == texture_map_.end());
  texture_pool_.destroy(tex);
}

TexturePool::texture_map_type::iterator TexturePool::find(const char *filename)
{
  texture_map_type::iterator i;
  if (texture_map_.empty()) {
    return texture_map_.end();
  }
  for (i = texture_map_.begin(); i != texture_map_.end(); ++i) {
    const char *fn = (*i).first;
    if (strcmp(fn, filename) == 0) {
      break;
    }
  }
  return i;
}
