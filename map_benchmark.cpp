#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cstddef>
#include <iostream>
#include <string>
#include <boost/progress.hpp>

#ifdef HAVE_TR1_UNORDERED_MAP
#include <tr1/unordered_map>
std::tr1::unordered_map<std::string, int> map1;
#endif
#ifdef HAVE_EXT_HASH_MAP
#include <ext/hash_map>
#include <boost/unordered_map.hpp>
__gnu_cxx::hash_map<std::string, int, boost::hash<std::string> > map2;
#endif
#ifdef HAVE_BOOST
#include <boost/unordered_map.hpp>
boost::unordered_map<const std::string, int> map3;
#endif
#ifdef STDCXX_98_HEADERS
#include <map>
std::map<const std::string, int> map4;
#endif

#define BM(f) {					\
    std::cout << #f << " ... ";			\
    boost::progress_timer t;			\
    for (int i = 0; i < 10000000; ++i) {	\
      (f);					\
    }						\
  }

int main()
{
#ifdef HAVE_TR1_UNORDERED_MAP
  BM(map1["foo"] = 123);
#endif
#ifdef HAVE_EXT_HASH_MAP
  BM(map2["foo"] = 123);
#endif
#ifdef HAVE_BOOST
  BM(map3["foo"] = 123);
#endif
#ifdef STDCXX_98_HEADERS
  BM(map4["foo"] = 123);
#endif
  return 0;
}
