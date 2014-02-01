#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "benchmark.hpp"

#ifdef HAVE_TR1_UNORDERED_MAP
#include <tr1/unordered_map>
std::tr1::unordered_map<std::string, int> map1;
#endif
//#ifdef HAVE_EXT_HASH_MAP
//#include <ext/hash_map>
//#include <boost/unordered_map.hpp>
//__gnu_cxx::hash_map<std::string, int, boost::hash<std::string> > map2;
//#endif
#ifdef HAVE_BOOST
#include <boost/unordered_map.hpp>
boost::unordered_map<const std::string, int> map3;
#endif
#ifdef STDCXX_98_HEADERS
#include <map>
std::map<const std::string, int> map4;
#endif

int main()
{
#ifdef HAVE_TR1_UNORDERED_MAP
  BM(std::tr1::unordered_map, map1["foo"] = 123);
#endif
  //#ifdef HAVE_EXT_HASH_MAP
  //  BM(__gnu_cxx::hash_map, map2["foo"] = 123);
  //#endif
#ifdef HAVE_BOOST
  BM(boost::unordered_map, map3["foo"] = 123);
#endif
#ifdef STDCXX_98_HEADERS
  BM(std::map, map4["foo"] = 123);
#endif
  return 0;
}
