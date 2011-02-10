#ifndef TEXTURE_POOL_HPP_INCLUDED
#define TEXTURE_POOL_HPP_INCLUDED 1

#include <string>
#include <boost/noncopyable.hpp>
#include <boost/pool/object_pool.hpp>
#include "sp.hpp"

#if defined(HAVE_TR1_UNORDERED_MAP)
#include <tr1/unordered_map>
#elif defined(HAVE_BOOST)
#include <boost/unordered_map.hpp>
#else
#include <map>
#endif

struct SDL_Renderer;
struct Texture;

class TexturePool : public boost::noncopyable
{
public:
  static TexturePool &get_instance();
  Texture *load_file(SDL_Renderer *renderer, const SP &filename);
  void destroy(Texture *tex);
private:
  typedef boost::object_pool<Texture> texture_pool_type;
#if defined(HAVE_TR1_UNORDERED_MAP)
  typedef std::tr1::unordered_map<std::string, Texture *> texture_map_type;
#elif defined(HAVE_BOOST)
  typedef boost::unordered_map<const std::string, Texture *> texture_map_type;
#else
  typedef std::map<const std::string, Texture *> texture_map_type;
#endif
  texture_pool_type texture_pool_;
  texture_map_type texture_map_;
  texture_map_type::iterator find(const SP &filename);
};

#endif // !defined(TEXTURE_POOL_HPP_INCLUDED)
