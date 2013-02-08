#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "vector_2d.hpp"
#include "point_2d.hpp"

/**
 * @brief コンストラクタ
 *
 * @param [in] p1 始点。
 * @param [in] p2 終点。
 */
Vector2D::Vector2D(const Point2D &p1, const Point2D &p2)
  : x(p2.x - p1.x)
  , y(p2.y - p1.y)
{
}
