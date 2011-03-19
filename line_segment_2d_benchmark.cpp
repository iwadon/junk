#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "line_segment_2d.hpp"
#include <cassert>
#include "benchmark.hpp"

int main()
{
  static bool r;
  LineSegment2D l1(0.0f, 0.0f, 1.0f, 1.0f);
  LineSegment2D l2(1.0f, 0.0f, 0.0f, 1.0f);
  LineSegment2D l3(0.5f, 0.5f, 1.0f, 0.0f);
  LineSegment2D l4(2.0f, 3.0f, 4.0f, 5.0f);
  LineSegment2D l5(1.0f, 0.0f, 0.6f, 0.4f);
  LineSegment2D l6(2.0f, 1.0f, 1.0f, 2.0f);
  BM(l1.is_crossed(l2), {
      r = l1.is_crossed(l2);
    });
  BM(l1.cross_point(l2), {
      r = l1.cross_point(l2);
    });
  BM(l1.is_crossed(l3), {
      r = l1.is_crossed(l3);
    });
  BM(l1.cross_point(l3), {
      r = l1.cross_point(l3);
    });
  BM(l1.is_crossed(l4), {
      r = l1.is_crossed(l4);
    });
  BM(l1.cross_point(l4), {
      r = l1.cross_point(l4);
    });
  BM(l1.is_crossed(l5), {
      r = l1.is_crossed(l5);
    });
  BM(l1.cross_point(l5), {
      r = l1.cross_point(l5);
    });
  BM(l1.is_crossed(l6), {
      r = l1.is_crossed(l6);
    });
  BM(l1.cross_point(l6), {
      r = l1.cross_point(l6);
    });
  return 0;
}
