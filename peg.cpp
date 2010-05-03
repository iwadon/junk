#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cstring>
#include "peg.hpp"

namespace peg
{
  Any any;

  Result Any::parse(const char *str)
  {
    Result result = {true, str + strlen(str)};
    return result;
  }
}
