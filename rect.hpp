#ifndef RECT_HPP_INCLUDED
#define RECT_HPP_INCLUDED 1

struct Rect
{
  float x;
  float y;
  float w;
  float h;

  Rect(const float x_, const float y_, const float w_, const float h_)
    : x(x_)
    , y(y_)
    , w(w_)
    , h(h_)
  {
  }

  bool is_intersected(const Rect &o) const
  {
    return x + w >= o.x && o.x + o.w >= x && y + h >= o.y && o.y + o.h >= y;
  }
};

#endif // !defined(RECT_HPP_INCLUDED)
