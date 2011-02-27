#ifndef LINE_SEGMENT_2D_HPP_INCLUDED
#define LINE_SEGMENT_2D_HPP_INCLUDED 1

#include "point_2d.hpp"
#include "vector_2d.hpp"

struct LineSegment2D
{
  Point2D p1;
  Point2D p2;

  LineSegment2D(const float x1, const float y1, const float x2, const float y2)
    : p1(x1, y1)
    , p2(x2, y2)
  {
  }

  bool is_crossed(const LineSegment2D &o) const
  {
    if (p1.x >= p2.x) {
      if ((p1.x < o.p1.x && p1.x < o.p2.x) || (p2.x > o.p1.x && p2.x > o.p2.x)) {
	return false;
      }
    } else {
      if ((p2.x < o.p1.x && p2.x < o.p2.x) || (p1.x > o.p1.x && p1.x > o.p2.x)) {
	return false;
      }
    }
    if (p1.y >= p2.y) {
      if ((p1.y < o.p1.y && p1.y < o.p2.y) || (p2.y > o.p1.y && p2.y > o.p2.y)) {
	return false;
      }
    } else {
      if ((p2.y < o.p1.y && p2.y < o.p2.y) || (p1.y > o.p1.y && p1.y > o.p2.y)) {
	return false;
      }
    }
    return side(o.p1) * side(o.p2) <= 0 && o.side(p1) * o.side(p2) <= 0;
  }

  std::string inspect() const
  {
    std::string s(p1.inspect());
    s += "-";
    s += p2.inspect();
    return s;
  }

  float length() const
  {
    return vector().length();
  }

  float side(const Point2D &p) const
  {
    return (p1.x - p2.x) * (p.y - p1.y) + (p1.y - p2.y) * (p1.x - p.x);
  }

  Vector2D vector() const
  {
    Vector2D v(p1.x - p2.x, p1.y - p2.y);
    return v;
  }
};

#endif // !defined(LINE_SEGMENT_2D_HPP_INCLUDED)
