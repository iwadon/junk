#ifndef BM_HPP_INCLUDED
#define BM_HPP_INCLUDED 1

#include <boost/progress.hpp>

#ifndef BM_COUNT
#define BM_COUNT 10000000
#endif

#ifndef BM_OUT
#include <iostream>
#define BM_OUT std::cout
#endif

#define BM(name, block) {				\
    BM_OUT << #name << " ... ";				\
      BM_OUT.flush();					\
      boost::progress_timer t(BM_OUT);			\
      for (unsigned int i = 0; i < BM_COUNT; ++i) {	\
	block;						\
      }							\
  }

#endif // !defined(BM_HPP_INCLUDED)
