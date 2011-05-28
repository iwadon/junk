#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "point_2d.hpp"
#include "vector_2d.hpp"

Point2D &Point2D::operator+=(const Vector2D &rhs)
{
  x += rhs.x;
  y += rhs.y;
  return *this;
}

Point2D Point2D::operator+(const Vector2D &rhs) const
{
  Point2D p(*this);
  p += rhs;
  return p;
}

/**
 * @brief 二つの点からベクトルを生成する
 *
 * rhsを始点とし、*thisを終点とするベクトルを生成します。
 *
 * @param [in] rhs 始点。
 *
 * @return ベクトル。
 */
Vector2D Point2D::operator-(const Point2D &rhs) const
{
  Vector2D v(rhs, *this);
  return v;
}

Point2D &Point2D::rotate(const float rad, const Point2D &center)
{
  float dx = x - center.x;
  float dy = y - center.y;
  float s = sinf(rad);
  float c = cosf(rad);
  x = dx * c - dy * s;
  y = dx * s + dy * c;
  return *this;
}
