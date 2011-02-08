#ifndef POINT_2D_HPP_INCLUDED
#define POINT_2D_HPP_INCLUDED 1

#include "vector_2d.hpp"

struct Point2D
{
  float x;
  float y;

  Point2D();
  Point2D(const float x, const float y);
  Point2D &operator+=(const Vector2D &rhs);
};

inline Point2D::Point2D()
  : x(0)
  , y(0)
{
}

inline Point2D::Point2D(const float x_, const float y_)
  : x(x_)
  , y(y_)
{
}

inline Point2D &Point2D::operator+=(const Vector2D &rhs)
{
  x += rhs.x;
  y += rhs.y;
  return *this;
}

#endif // !defined(POINT_2D_HPP_INCLUDED)
