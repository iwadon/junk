#ifndef CIRCULAR_BUFFER_HPP_INCLUDED
#define CIRCULAR_BUFFER_HPP_INCLUDED 1

#include <cstddef>

/// @brief 循環バッファです。
///
/// @tparam T 要素の型です。
/// @tparam N 要素の個数です。
template <class T, size_t N>
class CircularBuffer
{
public:
  /// @brief コンストラクタです。
  CircularBuffer()
    : size_(0)
    , read_pos_(0)
    , write_pos_(0)
  {
  }

  /// @brief バッファからデータを読み出します。
  ///
  /// @param[out] values 読み出したデータを格納するバッファです。
  /// @param[in] len     読み出すデータの個数です。
  ///
  /// @return 実際に読み出したデータの個数です。
  size_t Read(T *values, size_t len)
  {
    if (len > size_) {
      len = size_;
    }
    for (size_t i = 0; i < len; ++i) {
      values[i] = buf_[read_pos_];
      ++read_pos_;
      if (read_pos_ >= N) {
	read_pos_ -= N;
      }
    }
    size_ -= len;
    return len;
  }

  /// @brief バッファへデータを書き込みます。
  ///
  /// @param[in] values バッファへ書き込むデータの先頭アドレスです。
  /// @param[in] len    書き込むデータの個数です。
  ///
  /// @return 実際に書き込めたデータの個数です。
  size_t Write(const T *values, size_t len)
  {
    if (len > (N - size_)) {
      len = N - size_;
    }
    for (size_t i = 0; i < len; ++i) {
      buf_[write_pos_] = values[i];
      ++write_pos_;
      if (write_pos_ >= N) {
	write_pos_ -= N;
      }
    }
    size_ += len;
    return len;
  }

private:
  T buf_[N];
  size_t size_;
  size_t read_pos_;
  size_t write_pos_;
};

#endif // !defined(CIRCULAR_BUFFER_HPP_INCLUDED)
