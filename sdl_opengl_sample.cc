#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sdl_app.hpp"
#ifdef ENABLE_OPENGL
#include <SDL_opengl.h>
#endif
#include "point_2d.hpp"
#include "vector_2d.hpp"
#include <cstdio>
#include <memory>

class SDLOpenGLSampleApp : public SDLApp
{
public:
  SDLOpenGLSampleApp();
  void update();
  void draw();
protected:
  void draw_polygon(const Point2D &center, float size, float rad, int poly);
  void fill_polygon(const Point2D &center, float size, float rad, int poly);
private:
  float rad_;
  void setup_points_polygon(Point2D *points, const Point2D &center, float size, float rad, int poly);
};

SDLOpenGLSampleApp::SDLOpenGLSampleApp()
  : SDLApp("SDL OpenGL Sample")
  , rad_(0)
{
}

void SDLOpenGLSampleApp::update()
{
  rad_ += 0.01f;
}

void SDLOpenGLSampleApp::draw()
{
  draw_polygon(Point2D(500, 300), 100, rad_, 5);
  fill_polygon(Point2D(300, 300), 100, rad_, 5);
}

void SDLOpenGLSampleApp::draw_polygon(const Point2D &center, float size, float rad, int poly)
{
#ifdef ENABLE_OPENGL
  //Point2D points[poly];
  std::unique_ptr<Point2D[]> points(new Point2D[poly]);
  setup_points_polygon(points.get(), center, size, rad, poly);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < poly; ++i) {
    glVertex2f(points[i].x, points[i].y);
  }
  glEnd();
#endif
}

void SDLOpenGLSampleApp::fill_polygon(const Point2D &center, float size, float rad, int poly)
{
#ifdef ENABLE_OPENGL
  //Point2D points[poly];
  std::unique_ptr<Point2D[]> points(new Point2D[poly]);
  setup_points_polygon(points.get(), center, size, rad, poly);
  glBegin(GL_TRIANGLE_FAN);
  for (int i = 0; i < poly; ++i) {
    glVertex2f(points[i].x, points[i].y);
  }
  glEnd();
#endif
}

void SDLOpenGLSampleApp::setup_points_polygon(Point2D *points, const Point2D &center, float size, float rad, int poly)
{
  const float r = M_PI * 2 / poly;
  Point2D p(center);
  p.y -= size;
  p.rotate(rad, center);
  for (int i = 0; i < poly; ++i) {
    points[i] = p;
    p.rotate(r, center);
  }
}

int main(int argc, char *argv[])
{
  SDLOpenGLSampleApp app;
  return app.run(argc, argv);
}
