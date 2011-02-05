#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cmath>
#include <iostream>
#include <boost/progress.hpp>

float n;

#define BM(f) {					\
    std::cout << #f << " ... ";			\
    boost::progress_timer t;			\
    for (int i = 0; i < 10000000; ++i) {	\
      n = (f);					\
    }						\
  }

int main()
{
  float x = 2.0f;
  float y = 3.0f;
  BM(sqrt(x * x + y * y));
  BM(sqrtf(x * x + y * y));
  BM(hypot(x, y));
  BM(hypotf(x, y));
  return 0;
}
