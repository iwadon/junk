#ifndef POINT_HPP_INCLUDED
#define POINT_HPP_INCLUDED 1

#include "vector.hpp"

struct Point
{
  float x_;
  float y_;

  Point();
  Point(const float x, const float y);
  Point &operator+=(const Vector &rhs);
};

inline Point::Point()
  : x_(0)
  , y_(0)
{
}

inline Point::Point(const float x, const float y)
  : x_(x)
  , y_(y)
{
}

inline Point &Point::operator+=(const Vector &rhs)
{
  x_ += rhs.x_;
  y_ += rhs.y_;
  return *this;
}

#endif // !defined(POINT_HPP_INCLUDED)
