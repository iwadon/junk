#ifndef CIRCULAR_BUFFER_HPP_INCLUDED
#define CIRCULAR_BUFFER_HPP_INCLUDED 1

#include <cstddef>
#include <cstring>

/// 循環バッファ
template <size_t N>
class CircularBuffer
{
public:
  CircularBuffer(const size_t size)
  {
    set_size(size);
  }
  float get() const
  {
    return buf_[r_];
  }
  void set(const float value)
  {
    buf_[w_] = value;
  }
  void next()
  {
    ++r_;
    r_ %= size_ + 1;
    ++w_;
    w_ %= size_ + 1;
  }
  size_t size() const
  {
    return size_;
  }
  size_t capacity() const
  {
    return N;
  }
  void set_size(size_t new_size)
  {
    size_ = new_size;
    if (size_ < 1) {
      size_ = 1;
    } else if (size_ > N) {
      size_ = N;
    }
    memset(buf_, 0, sizeof (float) * (size_ + 1));
    r_ = 1;
    w_ = 0;
  }
private:
  float buf_[N + 1];
  size_t size_;
  size_t r_;
  size_t w_;
};

#endif // !defined(CIRCULAR_BUFFER_HPP_INCLUDED)
