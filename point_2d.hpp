#ifndef POINT_2D_HPP_INCLUDED
#define POINT_2D_HPP_INCLUDED 1

#include <ostream>
#include <string>
#include <SDL.h>

#ifdef _MSC_VER
#define snprintf _snprintf_s
#endif

struct Vector2D;

struct Point2D
{
  float x;
  float y;

  Point2D();
  Point2D(const float x, const float y);
  operator SDL_Point();
  operator const SDL_Point() const;
  Point2D &operator+=(const Vector2D &rhs);
  Point2D &operator-=(const Vector2D &rhs);
  Point2D operator+(const Vector2D &rhs) const;
  Vector2D operator-(const Point2D &rhs) const;
  bool operator==(const Point2D &rhs) const;
  std::string inspect() const;
  Point2D &rotate(const float rad, const Point2D &center);
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

inline Point2D::operator SDL_Point()
{
  SDL_Point p = {static_cast<int>(x), static_cast<int>(y)};
  return p;
}

inline Point2D::operator const SDL_Point() const
{
  const SDL_Point p = {static_cast<int>(x), static_cast<int>(y)};
  return p;
}

inline bool Point2D::operator==(const Point2D &rhs) const
{
  return x == rhs.x && y == rhs.y;
}

inline std::string Point2D::inspect() const
{
  char buf[256];
  snprintf(buf, sizeof buf, "(%.2f, %.2f)", x, y);
  std::string str(buf);
  return str;
}

static inline std::ostream &operator<<(std::ostream &os, const Point2D &p)
{
  os << p.inspect();
  return os;
}

#ifdef _MSC_VER
#undef snprintf
#endif

#endif // !defined(POINT_2D_HPP_INCLUDED)
