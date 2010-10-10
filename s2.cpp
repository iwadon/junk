#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef STDCXX_98_HEADERS
#include <list>
#endif
#ifdef HAVE_BOOST
#include <boost/foreach.hpp>
#include <boost/pool/object_pool.hpp>
#endif
#ifdef HAVE_SDL_H
#include <SDL.h>
#ifdef USE_OPENGL
#include <SDL_opengl.h>
#endif
#endif
#include "point.hpp"
#include "vector.hpp"
#include "sdl_app.hpp"

//#define SHOW_WINDOW_AFTER_INITIALIZED

namespace game
{
  static const float X_MIN = 0.0f;
  static const float X_MAX = 800.0f;
  static const float Y_MIN = 0.0f;
  static const float Y_MAX = 600.0f;
  static const float BOX_W = 10;
  static const float BOX_H = 10;
  static const size_t OBJ_NUM = 1000;

  class Object
  {
  public:
    Object();
    void move();
    void update();
    void draw();
  private:
    Point pos_;
    Vector spd_;
    Vector acc_;
  };

  class App : public SDLApp
  {
  public:
    App();
  protected:
    bool initialize(int argc, char *argv[]);
    void move();
    void update();
    void draw();
  private:
    SDL_Window *window_;
    bool done_;
    boost::object_pool<Object> objects;
    std::list<Object *> active_objects;
  };

  Object::Object()
  {
    pos_.x = (rand() * 1.0f / RAND_MAX) * 540 + (BOX_W / 2);
    pos_.y = (rand() * 1.0f / RAND_MAX) * 860 + (BOX_H / 2);
    spd_.x = (rand() * 1.0f / RAND_MAX) * 3;
    spd_.y = (rand() * 1.0f / RAND_MAX) * 3;
    acc_.x = 0.0f;
    acc_.y = 0.1f;
  }

  void Object::move()
  {
    if (pos_.y > Y_MAX - (BOX_H / 2)) {
      pos_.y = Y_MAX - (BOX_H / 2);
      spd_.y = -spd_.y;
    }
    if (pos_.x < X_MIN + (BOX_W / 2)) {
      pos_.x = X_MIN + (BOX_W / 2);
      spd_.x = -spd_.x;
    }
    if (pos_.x > X_MAX - (BOX_W / 2)) {
      pos_.x = X_MAX - (BOX_W / 2);
      spd_.x = -spd_.x;
    }
  }

  void Object::update()
  {
    spd_ += acc_;
    pos_ += spd_;
  }

  void Object::draw()
  {
#ifdef USE_OPENGL
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(pos_.x - (BOX_W / 2),  pos_.y - (BOX_H / 2));
    glVertex2f(pos_.x - (BOX_W / 2),  pos_.y + (BOX_H / 2));
    glVertex2f(pos_.x + (BOX_W / 2),  pos_.y + (BOX_H / 2));
    glVertex2f(pos_.x + (BOX_W / 2),  pos_.y - (BOX_H / 2));
    glEnd();
#else
    SDL_SetRenderDrawColor(0xf0, 0xf0, 0xf0, 0xff);
    SDL_Rect rect = {pos_.x - (BOX_W / 2), pos_.y - (BOX_H / 2), BOX_W, BOX_H};
    SDL_RenderFillRect(&rect);
#endif
  }

  App::App()
    : SDLApp("s2")
  {
  }

  bool App::initialize(int /*argc*/, char */*argv*/[])
  {
    if (!load_font_file("data/font5x5.png")) {
      return false;
    }

    for (size_t i = 0; i < OBJ_NUM; ++i) {
      Object *obj = objects.construct();
      active_objects.push_back(obj);
    }

    return true;
  }

  void App::move()
  {
    BOOST_FOREACH(Object *obj, active_objects) {
      obj->move();
    }
  }

  void App::update()
  {
    BOOST_FOREACH(Object *obj, active_objects) {
      obj->update();
    }
  }

  void App::draw()
  {
    BOOST_FOREACH(Object *obj, active_objects) {
      obj->draw();
    }
  }
} // namespace game

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char *argv[])
{
  game::App app;
  return app.run(argc, argv);
}
