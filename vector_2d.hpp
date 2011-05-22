#ifndef VECTOR_2D_HPP_INCLUDED
#define VECTOR_2D_HPP_INCLUDED 1

#include <cmath>
#include <ostream>

struct Vector2D
{
  float x;
  float y;

  Vector2D();
  Vector2D(const float x, const float y);
  static Vector2D angle_length(const float theta, const float len);
  float length() const;
  float inner_product(const Vector2D &o) const;
  Vector2D &operator+=(const Vector2D &rhs);
  Vector2D operator+(const Vector2D &rhs) const;
  Vector2D &operator*=(const float mul);
  Vector2D &operator*=(const Vector2D &rhs);
  Vector2D operator*(const float mul) const;
  Vector2D operator*(const Vector2D &rhs) const;
  bool operator==(const Vector2D &rhs) const;
  bool operator!=(const Vector2D &rhs) const;
  Vector2D &rotate(const float rad);
};

inline Vector2D::Vector2D()
  : x(0)
  , y(0)
{
}

inline Vector2D::Vector2D(const float x_, const float y_)
  : x(x_)
  , y(y_)
{
}

inline Vector2D Vector2D::angle_length(const float theta, const float len)
{
  Vector2D v;
  v.x = cos(theta) * len;
  v.y = sin(theta) * len;
  return v;
}

inline float Vector2D::length() const
{
  return sqrtf(x * x + y * y);
}

inline float Vector2D::inner_product(const Vector2D &o) const
{
  return x * o.x + y * o.y;
}

inline Vector2D &Vector2D::operator+=(const Vector2D &rhs)
{
  x += rhs.x;
  y += rhs.y;
  return *this;
}

inline Vector2D Vector2D::operator+(const Vector2D &rhs) const
{
  Vector2D v(*this);
  v += rhs;
  return v;
}

inline Vector2D &Vector2D::operator*=(const float mul)
{
  x *= mul;
  y *= mul;
  return *this;
}

inline Vector2D &Vector2D::operator*=(const Vector2D &rhs)
{
  x *= rhs.x;
  y *= rhs.y;
  return *this;
}

inline Vector2D Vector2D::operator*(const float mul) const
{
  Vector2D v(*this);
  v *= mul;
  return v;
}

inline Vector2D Vector2D::operator*(const Vector2D &rhs) const
{
  Vector2D v(*this);
  v *= rhs;
  return v;
}

inline bool Vector2D::operator==(const Vector2D &rhs) const
{
  return x == rhs.x && y == rhs.y;
}

inline bool Vector2D::operator!=(const Vector2D &rhs) const
{
  return !(*this == rhs);
}

inline Vector2D &Vector2D::rotate(const float theta)
{
  float s = sinf(theta);
  float c = cosf(theta);
  float tx = x * c - y * s;
  float ty = x * s + y * c;
  x = tx;
  y = ty;
  return *this;
}

static inline std::ostream &operator<<(std::ostream &os, const Vector2D &v)
{
  os << "(" << v.x << ", " << v.y << ")";
  return os;
}

#endif // !defined(VECTOR_HPP_INCLUDED)
