#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
//#define BM_COUNT 10000000
//#define BM_OUT std::cout
#include "benchmark.hpp"
#include <cmath>

int main()
{
  static float n;
  float x = 2.0f;
  float y = 3.0f;
  BM(sqrt, n = sqrt(x * x + y * y););
  BM(sqrtf, n = sqrtf(x * x + y * y););
  BM(hypot, {n = hypot(x, y);});
  BM(hypotf, {
      n = hypotf(x, y);
    });
  return 0;
}
