#ifndef TEXTURE_POOL_HPP_INCLUDED
#define TEXTURE_POOL_HPP_INCLUDED 1

#include <map>
#ifdef HAVE_BOOST
#include <boost/noncopyable.hpp>
#include <boost/pool/object_pool.hpp>
#endif
#include "texture.hpp"

class TexturePool : public boost::noncopyable
{
public:
  static TexturePool &get_instance();
  Texture *load_file(const char *filename);
  void destroy(Texture *tex);
private:
  typedef boost::object_pool<Texture> texture_pool_type;
  typedef std::map<const char *, Texture *> texture_map_type;
  texture_pool_type texture_pool_;
  texture_map_type texture_map_;
  TexturePool() {}
};

#endif // !defined(TEXTURE_POOL_HPP_INCLUDED)
