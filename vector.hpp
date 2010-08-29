#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED 1

struct Vector
{
  float x;
  float y;

  Vector();
  Vector(const float x, const float y);
  Vector &operator+=(const Vector &rhs);
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

inline Vector &Vector::operator+=(const Vector &rhs)
{
  x += rhs.x;
  y += rhs.y;
  return *this;
}

#endif // !defined(VECTOR_HPP_INCLUDED)
