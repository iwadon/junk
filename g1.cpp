#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "font.hpp"
#include "line_segment_2d.hpp"
#include "point_2d.hpp"
#include "sdl_app.hpp"

class App : public SDLApp
{
public:
  App();
protected:
  bool initialize(int argc, char *argv[]);
  void draw();
private:
  Point2D center_;
  float scale_;
  void line(const float x1, const float y1, const float x2, const float y2, uint32_t color);
  void line(const Point2D &p1, const Point2D &p2, uint32_t color);
  void line(const LineSegment2D &l, uint32_t color);
  void lines(const std::vector<Point2D> &ps, uint32_t color);
};

App::App()
  : SDLApp("g1")
  , center_(400, 300)
  , scale_(100)
{
}

bool App::initialize(int argc, char *argv[])
{
  set_bg_color(0xffffffff);

  return true;
}

void App::draw()
{
#if 0
  LineSegment2D l1(0.0f, 1.0f, 1.0f, 1.0f);
  LineSegment2D l2(0.0f, 0.0f, 0.8f, 1.5f);
  Point2D cp1;
  std::vector<Point2D> v;
  l2.bound(v, l1);

  line(l1, 0xff0000ff);
  lines(v, 0x0000ffff);
#endif
#if 0
  {
    LineSegment2D l1(0, -3, 0, 3);
    LineSegment2D l2(-1, 0, 0.5, 0.8);
    LineSegment2D l3(1, 1, -0.5, 1.8);
    LineSegment2D l4(1, -1, -0.5, -1.8);
    LineSegment2D l5(-1, -2, 0.5, -2.8);
    Point2D cp;
    std::vector<Point2D> v;
    line(l1, 0xff0000ff);
    if (l2.bound(v, l1)) {
      lines(v, 0x0000ffff);
    }
    v.clear();
    if (l3.bound(v, l1)) {
      lines(v, 0x00ff00ff);
    }
    v.clear();
    if (l4.bound(v, l1)) {
      lines(v, 0xffff00ff);
    }
    v.clear();
    if (l5.bound(v, l1)) {
      lines(v, 0xffff00ff);
    }
  }
#endif
  {
    LineSegment2D l1(0.0f, 2.0f, 2.0f, 0.0f);
    LineSegment2D l2(1.0f, 0.0f, 1.0f, 2.0f);
    std::vector<Point2D> v;
    line(l1, 0xff0000ff);
    if (l2.bound(v, l1)) {
      lines(v, 0x0000ffff);
    }
  }
}

void App::line(const float x1, const float y1, const float x2, const float y2, uint32_t color)
{
  SDL_SetRenderDrawColor(renderer(), (color >> 24) & 0xff, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff);
  SDL_RenderDrawLine(renderer(),
		     center_.x + x1 * scale_,
		     center_.y - y1 * scale_,
		     center_.x + x2 * scale_,
		     center_.y - y2 * scale_);
}

void App::line(const Point2D &p1, const Point2D &p2, uint32_t color)
{
  line(p1.x, p1.y, p2.x, p2.y, color);
}

void App::line(const LineSegment2D &l, uint32_t color)
{
  line(l.p1, l.p2, color);
}

void App::lines(const std::vector<Point2D> &ps, uint32_t color)
{
  for (size_t i = 0; i < ps.size() - 1; ++i) {
    line(ps[i], ps[i + 1], color);
  }
}

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char *argv[])
{
  App app;
  return app.run(argc, argv);
}
