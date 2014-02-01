/**
 * @file lot_box.hpp
 * @brief LotBoxクラスの定義と実装
 */
#ifndef LOT_BOX_HPP_INCLUDED
#define LOT_BOX_HPP_INCLUDED 1

#include <array>
#include <random>

/**
 * @brief 抽選箱
 * @tparam N くじの総数。
 * @tparam M 当たりくじの数。
 * @sa http://ameblo.jp/evezoo/entry-10704872133.html
 */
template <size_t N, size_t M>
class LotBox
{
public:
  /**
   * @brief コンストラクタ
   * @param [in] seed 乱数の種。
   */
  LotBox(std::mt19937::result_type seed)
    : rng_(seed)
    , dist_(1, N)
    , n_(0)
  {
    reset();
  }
  /**
   * @brief くじをひく
   * @retval true  当たりをひいた。
   * @retval false ハズレを引いた。
   */
  bool draw()
  {
    ++n_;
    if (n_ > N) {
      n_ -= N;
      reset();
    }
    return std::find(winning_numbers_.begin(), winning_numbers_.end(), n_) != winning_numbers_.end();
  }
  /**
   * @brief くじを作り直す
   */
  void reset()
  {
    for (size_t i = 0; i < M; ++i) {
      winning_numbers_[i] = dist_(rng_);
    }
  }
private:
  std::mt19937 rng_;
  std::uniform_int_distribution<> dist_;
  std::array<size_t, M> winning_numbers_;
  size_t n_;
};

#endif // !defined(LOT_BOX_HPP_INCLUDED)
