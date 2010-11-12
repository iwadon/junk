#ifndef CONTROLLER_HPP_INCLUDED
#define CONTROLLER_HPP_INCLUDED 1

#ifdef STDCXX_98_HEADERS
#include <vector>
#endif
#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST_CSTDINT_HPP)
#include <boost/cstdint.hpp>
#endif
#ifdef HAVE_SDL_H
#include <SDL.h>
#endif

class Controller
{
public:
  struct Data
  {
    struct Key
    {
      uint32_t status;
      uint32_t on;
      uint32_t off;
      bool operator==(const Key &x) const {
	return status == x.status && on == x.on && off == x.off;
      }
      bool operator!=(const Key &x) const {
	return !(*this == x);
      }
    };
    Key key;
  };
  void update(const SDL_Event &event);
  bool is_updated() const { return updated_; }
  const Data &latest_data() const { return data_list.empty() ? empty_data_ : data_list.back(); }
private:
  std::vector<Data> data_list;
  bool updated_;
  static const Data empty_data_;
};

#endif // !defined(CONTROLLER_HPP_INCLUDED)
