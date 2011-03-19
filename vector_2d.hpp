#ifndef VECTOR_2D_HPP_INCLUDED
#define VECTOR_2D_HPP_INCLUDED 1

#include <cmath>
#include <ostream>

struct Point2D;

struct Vector2D
{
  union {
    struct {
      float x;
      float y;
    };
    float values[2];
  };

  Vector2D();
  Vector2D(const float x, const float y);
  Vector2D(const Point2D &p1, const Point2D &p2);

  operator float *();
  operator const float *() const;

  Vector2D &operator+=(const Vector2D &rhs);
  Vector2D &operator-=(const Vector2D &rhs);
  Vector2D &operator*=(const float mul);
  Vector2D &operator*=(const Vector2D &rhs);
  Vector2D &operator/=(const float mul);
  Vector2D &operator/=(const Vector2D &rhs);

  Vector2D operator+() const;
  Vector2D operator-() const;

  Vector2D operator+(const Vector2D &rhs) const;
  Vector2D operator-(const Vector2D &rhs) const;
  Vector2D operator*(const float mul) const;
  Vector2D operator*(const Vector2D &rhs) const;
  Vector2D operator/(const float div) const;
  Vector2D operator/(const Vector2D &rhs) const;

  bool operator==(const Vector2D &rhs) const;
  bool operator!=(const Vector2D &rhs) const;

  static Vector2D angle_length(const float theta, const float len);
  float cross(const Vector2D &rhs) const;
  float dot(const Vector2D &rhs) const;
  float length() const;
  Vector2D &normalize();
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

inline Vector2D::operator float *()
{
  return values;
}

inline Vector2D::operator const float *() const
{
  return values;
}

inline Vector2D &Vector2D::operator+=(const Vector2D &rhs)
{
  x += rhs.x;
  y += rhs.y;
  return *this;
}

inline Vector2D &Vector2D::operator-=(const Vector2D &rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  return *this;
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

inline Vector2D &Vector2D::operator/=(const float mul)
{
  x /= mul;
  y /= mul;
  return *this;
}

inline Vector2D &Vector2D::operator/=(const Vector2D &rhs)
{
  x /= rhs.x;
  y /= rhs.y;
  return *this;
}

inline Vector2D Vector2D::operator+() const
{
  return *this;
}

inline Vector2D Vector2D::operator-() const
{
  Vector2D v(-x, -y);
  return v;
}

inline Vector2D Vector2D::operator+(const Vector2D &rhs) const
{
  Vector2D v(*this);
  v += rhs;
  return v;
}

inline Vector2D Vector2D::operator-(const Vector2D &rhs) const
{
  Vector2D v(*this);
  v -= rhs;
  return v;
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

inline Vector2D Vector2D::operator/(const float div) const
{
  Vector2D v(*this);
  v /= div;
  return v;
}

inline Vector2D Vector2D::operator/(const Vector2D &rhs) const
{
  Vector2D v(*this);
  v /= rhs;
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

inline Vector2D Vector2D::angle_length(const float theta, const float len)
{
  Vector2D v;
  v.x = cos(theta) * len;
  v.y = sin(theta) * len;
  return v;
}

/**
 * @brief 二つのベクトルの外積を求める
 *
 * @param [in] rhs もう一方のベクトル。
 *
 * @return 二つのベクトルの外積。
 */
inline float Vector2D::cross(const Vector2D &rhs) const
{
  return x * rhs.y - y * rhs.x;
}

/**
 * @brief 二つのベクトルの内積を求める
 *
 * @param [in] rhs もう一方のベクトル。
 *
 * @return 二つのベクトルの内積。
 */
inline float Vector2D::dot(const Vector2D &rhs) const
{
  return x * rhs.x + y * rhs.y;
}

inline float Vector2D::length() const
{
  return sqrtf(x * x + y * y);
}

/**
 * @brief 単位ベクトル化する
 *
 * @return *this。
 */
inline Vector2D &Vector2D::normalize()
{
  float len = length();
  x /= len;
  y /= len;
  return *this;
}

inline Vector2D &Vector2D::rotate(const float theta)
{
  float s = sin(theta);
  float c = cos(theta);
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
