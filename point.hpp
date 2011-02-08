#ifndef POINT_HPP_INCLUDED
#define POINT_HPP_INCLUDED 1

#include "vector.hpp"

struct Point
{
  float x;
  float y;

  Point();
  Point(const float x, const float y);
  Point &operator+=(const Vector2D &rhs);
};

inline Point::Point()
  : x(0)
  , y(0)
{
}

inline Point::Point(const float x_, const float y_)
  : x(x_)
  , y(y_)
{
}

inline Point &Point::operator+=(const Vector2D &rhs)
{
  x += rhs.x;
  y += rhs.y;
  return *this;
}

#endif // !defined(POINT_HPP_INCLUDED)
