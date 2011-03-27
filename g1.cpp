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
  if (!load_font_file("data/font5x5.png")) {
    return false;
  }

  set_bg_color(0xffffffff);

  return true;
}

void App::draw()
{
  LineSegment2D l1(0.0f, 1.0f, 1.0f, 1.0f);
  LineSegment2D l2(0.0f, 0.0f, 0.8f, 1.5f);
  Point2D cp1;
  //l1.cross_point(l2, &cp1);
  //l1.intersection_point_with(cp1, l2);
  std::vector<Point2D> v;
  l2.bound(v, l1);

  line(l1, 0xff0000ff);
  //line(l2.p1, cp1, 0x00ff00ff);
  //line(cp1.x, cp1.y, l2.p2.x, cp1.y - (l2.p2.y - cp1.y), 0x0000ffff);
  lines(v, 0x0000ffff);
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
