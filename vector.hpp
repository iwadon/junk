#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED 1

#include <cmath>
#include <ostream>

struct Vector
{
  float x;
  float y;

  Vector();
  Vector(const float x, const float y);
  static Vector angle_length(const float theta, const float len);
  float length() const;
  float inner_product(const Vector &o) const;
  Vector &operator+=(const Vector &rhs);
  Vector operator+(const Vector &rhs) const;
  Vector &operator*=(const float mul);
  Vector &operator*=(const Vector &rhs);
  Vector operator*(const float mul) const;
  Vector operator*(const Vector &rhs) const;
  bool operator==(const Vector &rhs) const;
  bool operator!=(const Vector &rhs) const;
  Vector &rotate(const float rad);
};

inline Vector::Vector()
  : x(0)
  , y(0)
{
}

inline Vector::Vector(const float x_, const float y_)
  : x(x_)
  , y(y_)
{
}

inline Vector Vector::angle_length(const float theta, const float len)
{
  Vector v;
  v.x = cos(theta) * len;
  v.y = sin(theta) * len;
  return v;
}

inline float Vector::length() const
{
  return sqrtf(x * x + y * y);
}

inline float Vector::inner_product(const Vector &o) const
{
  return x * o.x + y * o.y;
}

inline Vector &Vector::operator+=(const Vector &rhs)
{
  x += rhs.x;
  y += rhs.y;
  return *this;
}

inline Vector Vector::operator+(const Vector &rhs) const
{
  Vector v(*this);
  v += rhs;
  return v;
}

inline Vector &Vector::operator*=(const float mul)
{
  x *= mul;
  y *= mul;
  return *this;
}

inline Vector &Vector::operator*=(const Vector &rhs)
{
  x *= rhs.x;
  y *= rhs.y;
  return *this;
}

inline Vector Vector::operator*(const float mul) const
{
  Vector v(*this);
  v *= mul;
  return v;
}

inline Vector Vector::operator*(const Vector &rhs) const
{
  Vector v(*this);
  v *= rhs;
  return v;
}

inline bool Vector::operator==(const Vector &rhs) const
{
  return x == rhs.x && y == rhs.y;
}

inline bool Vector::operator!=(const Vector &rhs) const
{
  return !(*this == rhs);
}

inline Vector &Vector::rotate(const float theta)
{
  float s = sin(theta);
  float c = cos(theta);
  float tx = x * c - y * s;
  float ty = x * s + y * c;
  x = tx;
  y = ty;
  return *this;
}

static inline std::ostream &operator<<(std::ostream &os, const Vector &v)
{
  os << "(" << v.x << ", " << v.y << ")";
  return os;
}

#endif // !defined(VECTOR_HPP_INCLUDED)
