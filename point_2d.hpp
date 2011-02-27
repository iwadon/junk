#ifndef POINT_2D_HPP_INCLUDED
#define POINT_2D_HPP_INCLUDED 1

#include <cstring>
#include <string>
#include "vector_2d.hpp"

struct Point2D
{
  float x;
  float y;

  Point2D();
  Point2D(const float x, const float y);
  Point2D &operator+=(const Vector2D &rhs);
  std::string inspect() const;
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

inline std::string Point2D::inspect() const
{
  char buf[256];
  snprintf(buf, sizeof buf, "(%.2f, %.2f)", x, y);
  std::string str(buf);
  return str;
}

#endif // !defined(POINT_2D_HPP_INCLUDED)
