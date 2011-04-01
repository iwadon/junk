#ifndef LINE_SEGMENT_2D_HPP_INCLUDED
#define LINE_SEGMENT_2D_HPP_INCLUDED 1

#include <vector>
#include "point_2d.hpp"
#include "vector_2d.hpp"

struct LineSegment2D
{
  Point2D p1;
  Point2D p2;

  /**
   * @brief コンストラクタ
   *
   * @param [in] x1 始点のX座標。
   * @param [in] y1 始点のY座標。
   * @param [in] x2 終点のX座標。
   * @param [in] y2 終点のY座標。
   */
  LineSegment2D(const float x1, const float y1, const float x2, const float y2)
    : p1(x1, y1)
    , p2(x2, y2)
  {
  }

  /**
   * @brief コンストラクタ
   *
   * @param [in] p1 始点。
   * @param [in] p2 終点。
   */
  LineSegment2D(const Point2D &p1_, const Point2D &p2_)
    : p1(p1_)
    , p2(p2_)
  {
  }

  /**
   * @brief 線分をもう一方の線分に弾ませた結果を返す
   *
   * @param [out] v     結果を格納するコンテナ。
   *                    もし線分が弾んだならばvには三つのPoint2Dオブジェクトがpush_backされる。
   *                    (1)弾ませた線分の始点(p1) (2)線分が弾んだ点(交点) (3)線分が弾んだ先を示す点
   * @param [in]  other 線分を弾ませる相手の線分。
   *
   * @retval true  線分は弾んだ(交差した)。
   * @retval false 線分は弾まない(交差しない)。
   */
  bool bound(std::vector<Point2D> &v, const LineSegment2D &other)
  {
    if (other.p1.y == other.p2.y) {
      Point2D cp;
      if (!intersection_point_with(cp, other)) {
	return false;
      }
      Point2D p(p2.x, cp.y - (p2.y - cp.y));
      v.push_back(p1);
      v.push_back(cp);
      v.push_back(p);
      return true;
    } else if (other.p1.x == other.p2.x) {
      Point2D cp;
      if (!intersection_point_with(cp, other)) {
	return false;
      }
      Point2D p(cp.x - (p2.x - cp.x), p2.y);
      v.push_back(p1);
      v.push_back(cp);
      v.push_back(p);
      return true;
    } else {
      Point2D cp;
      float t2;
      if (!cross_point(other, &cp, NULL, &t2)) {
	return false;
      }
      //cp + vector() * t2;
      Point2D p(cp + vector().reflect(other.vector().rotate(M_PI / 2)) * t2);
      v.push_back(p1);
      v.push_back(cp);
      v.push_back(p);
      return true;
    }
  }

  /**
   * @brief 二つの線分の交点を返す
   *
   * @param [in]  o  もう一方の線分。
   * @param [out] cp 交点。二つの線分が交差していないならば更新されない。
   * @param [out] t1 線分 *this の内分比。二つの線分が平行な状態ならば更新されない。
   * @param [out] t2 線分 o の内分比。二つの線分が平行な状態ならば更新されない。
   *
   * @retval true  交差している。
   * @retval false 交差していない。
   */
  bool cross_point(const LineSegment2D &o, Point2D *cp = NULL, float *t1 = NULL, float *t2 = NULL) const
  {
    Vector2D v = o.p1 - p1;
    Vector2D v1 = vector();
    Vector2D v2 = o.vector();
    float v1v2 = v1.cross(v2);
    if (v1v2 == 0.0f) {
      return false;
    }
    float vv1 = v.cross(v1);
    float vv2 = v.cross(v2);
    float t1_ = vv2 / v1v2;
    float t2_ = vv1 / v1v2;
    if (t1 != NULL) {
      *t1 = t1_;
    }
    if (t2 != NULL) {
      *t2 = t2_;
    }
    static const float EPS = 0.00001f;
    if (t1_ + EPS < 0.0f || t1_ - EPS > 1.0f || t2_ + EPS < 0.0f || t2_ - EPS > 1.0f) {
      return false;
    }
    if (cp != NULL) {
      *cp = p1 + vector() * t1_;
    }
    return true;
  }

  /**
   * @brief 二つの線分が交差しているかどうかを返す
   *
   * @param [in] もう一方の線分。
   *
   * @retval true  二つの線分は交差している。
   * @retval false 二つの線分は交差していない。
   */
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

  /**
   * @brief オブジェクトの内容を示す文字列を返す
   *
   * @return オブジェクトの内容を示す文字列。
   */
  std::string inspect() const
  {
    std::string s(p1.inspect());
    s += "-";
    s += p2.inspect();
    return s;
  }

  /**
   * @brief 他の線分との交点を返す
   *
   * @param [out] p 交点。
   * @param [in]  o 他の線分。
   *
   * @retval true  正常に交点を求められました。
   * @retval false 交点はありませんでした。
   */
  bool intersection_point_with(Point2D &p, const LineSegment2D &o)
  {
    if (!is_crossed(o)) {
      return false;
    }
    float r = ((o.p2.y - o.p1.y) * (o.p1.x - p1.x) - (o.p2.x - o.p1.x) * (o.p1.y - p1.y)) / ((p2.x - p1.x) * (o.p2.y - o.p1.y) - (p2.y - p1.y) * (o.p2.x - o.p1.x));
    p = p1 + r * (p2 - p1);
    return true;
  }

  /**
   * @brief 線分の長さを返す
   *
   * @return 線分の長さ。
   */
  float length() const
  {
    return vector().length();
  }

  /**
   * @brief 点が線分のどちら側にあるかを返す
   *
   * @return 点がある側。
   */
  float side(const Point2D &p) const
  {
    return (p1.x - p2.x) * (p.y - p1.y) + (p1.y - p2.y) * (p1.x - p.x);
  }

  /**
   * @brief p1からp2へのベクトルを生成する
   *
   * @return p1からp2へのベクトル。
   */
  Vector2D vector() const
  {
    Vector2D v(p2.x - p1.x, p2.y - p1.y);
    return v;
  }
};

#endif // !defined(LINE_SEGMENT_2D_HPP_INCLUDED)
