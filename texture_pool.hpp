#ifndef TEXTURE_POOL_HPP_INCLUDED
#define TEXTURE_POOL_HPP_INCLUDED 1

#ifdef STDCXX_98_HEADERS
#include <map>
#include <string>
#endif
#ifdef HAVE_BOOST
#include <boost/noncopyable.hpp>
#include <boost/pool/object_pool.hpp>
#endif
#include "sp.hpp"

struct Texture;

class TexturePool : public boost::noncopyable
{
public:
  static TexturePool &get_instance();
  Texture *load_file(const SP &filename);
  void destroy(Texture *tex);
private:
  typedef boost::object_pool<Texture> texture_pool_type;
  typedef std::map<const std::string, Texture *> texture_map_type;
  texture_pool_type texture_pool_;
  texture_map_type texture_map_;
  texture_map_type::iterator find(const SP &filename);
};

#endif // !defined(TEXTURE_POOL_HPP_INCLUDED)
