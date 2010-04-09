#ifndef VOLUME_HPP_INCLUDED
#define VOLUME_HPP_INCLUDED 1

template <class V, class F>
class Volume
{
public:
  Volume(const V value);
  void update();
  V get() const { return value_; }
  void set(const V value, const F frames = 0);
  bool is_updated() const { return (flag_ & FLAG_UPDATED) != 0; }
private:
  typedef uint32_t FLAG;

  static const FLAG FLAG_UPDATED = 1 << 0;
  static const FLAG FLAG_FORCE_UPDATE = 1 << 1;

  V value_;
  F frames_;
  V goal_;
  V increment_;
  FLAG flag_;
};

template <class V, class F>
inline Volume<V, F>::Volume(const V value)
  : value_(value)
  , frames_(0)
  , goal_(0)
  , increment_(0)
  , flag_(0)
{
}

template <class V, class F>
inline void Volume<V, F>::update()
{
  if (flag_ & FLAG_FORCE_UPDATE) {
    flag_ |= FLAG_UPDATED;
    flag_ &= ~FLAG_FORCE_UPDATE;
  } else {
    flag_ &= ~FLAG_UPDATED;
  }
  if (frames_ > 0) {
    --frames_;
    if (frames_ == 0) {
      value_ = goal_;
      increment_ = 0;
    } else {
      value_ += increment_;
    }
    flag_ |= FLAG_UPDATED;
  }
}

template <class V, class F>
inline void Volume<V, F>::set(const V goal, const F frames)
{
  goal_ = goal;
  frames_ = frames;
  if (frames_ == 0) {
    value_ = goal_;
    increment_ = 0;
    flag_ |= FLAG_FORCE_UPDATE;
  } else {
    increment_ = (goal_ - value_) / frames;
  }
}

#endif // !defined(VOLUME_HPP_INCLUDED)
