#ifndef BM_HPP_INCLUDED
#define BM_HPP_INCLUDED 1

#include <chrono>

#ifndef BM_COUNT
#define BM_COUNT 10000000
#endif

#ifndef BM_OUT
#include <iostream>
#define BM_OUT std::cout
#endif

#define BM(name, block) {					\
    BM_OUT << #name << " ... ";					\
    BM_OUT.flush();						\
    auto start = std::chrono::system_clock::now();		\
    for (unsigned int i = 0; i < BM_COUNT; ++i) {		\
      block;							\
    }								\
    auto end = std::chrono::system_clock::now();		\
    auto d = end - start;						\
    BM_OUT << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << "ms\n"; \
  }

#endif // !defined(BM_HPP_INCLUDED)
