#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED 1

struct Vector
{
  float x_;
  float y_;

  Vector();
  Vector(const float x, const float y);
  Vector &operator+=(const Vector &rhs);
};

inline Vector::Vector()
  : x_(0)
  , y_(0)
{
}

inline Vector::Vector(const float x, const float y)
  : x_(x)
  , y_(y)
{
}

inline Vector &Vector::operator+=(const Vector &rhs)
{
  x_ += rhs.x_;
  y_ += rhs.y_;
  return *this;
}

#endif // !defined(VECTOR_HPP_INCLUDED)
