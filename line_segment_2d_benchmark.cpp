#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "line_segment_2d.hpp"
#include <cassert>
#include "benchmark.hpp"
#include "point_2d.hpp"

#define B(code) BM(code, {r = code;})

int main()
{
  static bool r;
  LineSegment2D l1(0.0f, 0.0f, 1.0f, 1.0f);
  LineSegment2D l2(1.0f, 0.0f, 0.0f, 1.0f);
  LineSegment2D l3(0.5f, 0.5f, 1.0f, 0.0f);
  LineSegment2D l4(2.0f, 3.0f, 4.0f, 5.0f);
  LineSegment2D l5(1.0f, 0.0f, 0.6f, 0.4f);
  LineSegment2D l6(2.0f, 1.0f, 1.0f, 2.0f);
  Point2D cp;
  B(l1.is_crossed(l2));
  B(l1.intersection_point_with(cp, l2));
  B(l1.cross_point(l2));
  B(l1.cross_point(l2, &cp));
  B(l1.is_crossed(l3));
  B(l1.intersection_point_with(cp, l3));
  B(l1.cross_point(l3));
  B(l1.cross_point(l3, &cp));
  B(l1.is_crossed(l4));
  B(l1.intersection_point_with(cp, l4));
  B(l1.cross_point(l4));
  B(l1.cross_point(l4, &cp));
  B(l1.is_crossed(l5));
  B(l1.intersection_point_with(cp, l5));
  B(l1.cross_point(l5));
  B(l1.cross_point(l5, &cp));
  B(l1.is_crossed(l6));
  B(l1.intersection_point_with(cp, l6));
  B(l1.cross_point(l6));
  B(l1.cross_point(l6, &cp));
  return 0;
}
