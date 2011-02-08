#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED 1

#include <cmath>

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
  Vector rotate(const float rad) const;
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

inline Vector Vector::rotate(const float theta) const
{
  Vector v;
  float s = sin(theta);
  float c = cos(theta);
  v.x = x * c - y * s;
  v.y = x * s + y * c;
  return v;
}

#endif // !defined(VECTOR_HPP_INCLUDED)
