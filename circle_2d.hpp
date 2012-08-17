#ifndef CIRCLE_2D_HPP_INCLUDED
#define CIRCLE_2D_HPP_INCLUDED 1

#include "line_segment_2d.hpp"
#include "point_2d.hpp"

/// 円
struct Circle2D
{
  Point2D center;		///< 中心点
  float radius;			///< 半径

  /// コンストラクタ
  Circle2D()
    : center(0.0f, 0.0f)
    , radius(0.0f)
  {
  }

  /// コンストラクタ
  Circle2D(const float x, const float y, const float r)
    : center(x, y)
    , radius(r)
  {
  }

  /// コンストラクタ
  Circle2D(const Point2D &p, const float r)
    : center(p)
    , radius(r)
  {
  }

  // 点が円に含まれるかどうかを返す
  bool is_include(const Point2D &p)
  {
    return LineSegment2D(center.x, center.y, p.x, p.y).length() <= radius;
  }

  // 円同士が重なり合っているかどうかを返す
  bool is_collide(const Circle2D &c)
  {
    return LineSegment2D(center.x, center.y, c.center.x, c.center.y).length() <= radius + c.radius;
  }
};

#endif // !defined(CIRCLE_2D_HPP_INCLUDED)
