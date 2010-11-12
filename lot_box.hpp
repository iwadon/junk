#ifndef LOT_BOX_HPP_INCLUDED
#define LOT_BOX_HPP_INCLUDED 1

#ifdef HAVE_BOOST
#include <boost/array.hpp>
#include <boost/random.hpp>
#endif

// Lot Box class
// This class is based on the lot box method.
// http://ameblo.jp/evezoo/entry-10704872133.html
template <size_t N, size_t M>
class LotBox
{
public:
  LotBox()
    : rng_()
    , dst_(1, N)
    , rand_(rng_, dst_)
    , n_(0)
  {
    reset();
  }
  LotBox(boost::mt19937::result_type seed)
    : rng_(seed)
    , dst_(1, N)
    , rand_(rng_, dst_)
    , n_(0)
  {
    reset();
  }
  bool draw()
  {
    ++n_;
    if (n_ > N) {
      n_ -= N;
      reset();
    }
    return std::find(winning_numbers_.begin(), winning_numbers_.end(), n_) != winning_numbers_.end();
  }
  void reset()
  {
    for (size_t i = 0; i < M; ++i) {
      winning_numbers_[i] = rand_();
    }
  }
private:
  boost::mt19937 rng_;
  boost::uniform_int<> dst_;
  boost::variate_generator<boost::mt19937 &, boost::uniform_int<> > rand_;
  boost::array<size_t, N> winning_numbers_;
  size_t n_;
};

#endif // !defined(LOT_BOX_HPP_INCLUDED)
