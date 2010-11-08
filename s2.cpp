#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef STDCXX_98_HEADERS
#include <list>
#endif
#ifdef HAVE_BOOST
#include <boost/foreach.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/shared_ptr.hpp>
#endif
#ifdef HAVE_SDL_H
#include <SDL.h>
#include <SDL_opengl.h>
#endif
#include "logger.hpp"
#include "point.hpp"
#include "sdl_app.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include "vector.hpp"

//#define SHOW_WINDOW_AFTER_INITIALIZED

namespace game
{
  static const float X_MIN = 0.0f;
  static const float X_MAX = 800.0f;
  static const float Y_MIN = 0.0f;
  static const float Y_MAX = 600.0f;
  static const float DEMOBOX_W = 10;
  static const float DEMOBOX_H = 10;
  static const float MYSHIP_W = 30;
  static const float MYSHIP_H = 50;
  static const size_t OBJ_NUM = 500;

  class Object
  {
  public:
    virtual ~Object() {}
    virtual void initialize() {}
    virtual void input() {}
    virtual void move() {}
    virtual void update();
    virtual void draw() {}
  protected:
    Point pos_;
    Vector spd_;
    Vector acc_;
    float rot_;
    float scale_;
  };

  class DemoBox : public Object
  {
  public:
    DemoBox();
    void initialize();
    void move();
    void draw();
  private:
    boost::shared_ptr<Sprite> sprite_;
  };

  class MyShip : public Object
  {
  public:
    void initialize();
    void input();
    void move();
    void draw();
  };

  class App : public SDLApp
  {
  public:
    App();
  protected:
    bool initialize(int argc, char *argv[]);
    void input();
    void move();
    void update();
    void draw();
  private:
    SDL_Window *window_;
    bool done_;
    std::list<Object *> active_objects;
  };

  void Object::update()
  {
    spd_ += acc_;
    pos_ += spd_;
  }

  DemoBox::DemoBox()
    : sprite_(new Sprite)
  {
  }

  void DemoBox::initialize()
  {
    pos_.x = (rand() * 1.0f / RAND_MAX) * X_MAX - (DEMOBOX_W / 2);
    pos_.y = (rand() * 1.0f / RAND_MAX) * Y_MAX - (DEMOBOX_H / 2);
    spd_.x = (rand() * 1.0f / RAND_MAX) * 2.5f;
    spd_.y = (rand() * 1.0f / RAND_MAX) * 2.5f;
    acc_.x = 0.0f;
    acc_.y = 0.1f;
    rot_ = (rand() * 1.0f / RAND_MAX) * 360.0f;
    //scale_ = (rand() * 1.0f / RAND_MAX) * 9.0f + 1.0f;
    scale_ = 1.0f;
    SDL_Rect r = {0, 0, 100, 100};
    sprite_->set_texture("data/blue_box.png", &r);
  }

  void DemoBox::move()
  {
    if (pos_.y > Y_MAX - (DEMOBOX_H / 2)) {
      pos_.y = Y_MAX - (DEMOBOX_H / 2);
      spd_.y = -spd_.y;
    }
    if (pos_.x < X_MIN + (DEMOBOX_W / 2)) {
      pos_.x = X_MIN + (DEMOBOX_W / 2);
      spd_.x = -spd_.x;
    }
    if (pos_.x > X_MAX - (DEMOBOX_W / 2)) {
      pos_.x = X_MAX - (DEMOBOX_W / 2);
      spd_.x = -spd_.x;
    }
    rot_ += 5.5f;
    if (rot_ >= 360.0f) {
      rot_ -= 360.0f;
    }
#if 0
    scale_ += 0.03f;
    if (scale_ >= 3.0f) {
      scale_ -= 3.0f - 0.03f;
    }
#endif
  }

  void DemoBox::draw()
  {
    glPushMatrix();
    sprite_->pos = pos_;
    sprite_->rot = rot_;
    sprite_->scale = scale_;
    sprite_->draw();
    glPopMatrix();
  }

  void MyShip::initialize()
  {
    pos_.x = (X_MAX - X_MIN) / 2;
    pos_.y = (Y_MAX - Y_MIN) * 3 / 4;
    spd_.x = 0;
    spd_.y = 0;
    acc_.x = 0;
    acc_.y = 0;
    rot_ = 0;
    scale_ = 1;
  }

  void MyShip::input()
  {
  }

  void MyShip::move()
  {
  }

  void MyShip::draw()
  {
    glPushMatrix();
    glTranslatef(pos_.x, pos_.y, 0.0f);
    glRotatef(rot_, 0.0f, 0.0f, 1.0f);
    glScalef(scale_, scale_, 1.0f);
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-(MYSHIP_W / 2), -(MYSHIP_H / 2));
    glVertex2f(-(MYSHIP_W / 2),  (MYSHIP_H / 2));
    glVertex2f( (MYSHIP_W / 2),  (MYSHIP_H / 2));
    glVertex2f( (MYSHIP_W / 2), -(MYSHIP_H / 2));
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-(MYSHIP_W / 2), -(MYSHIP_H / 2));
    glVertex2f(-(MYSHIP_W / 2),  (MYSHIP_H / 2));
    glVertex2f( (MYSHIP_W / 2),  (MYSHIP_H / 2));
    glVertex2f( (MYSHIP_W / 2), -(MYSHIP_H / 2));
    glEnd();
    glPopMatrix();
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
      Object *obj = new DemoBox;
      obj->initialize();
      active_objects.push_back(obj);
    }

    Object *obj = new MyShip;
    obj->initialize();
    active_objects.push_back(obj);

    return true;
  }

  void App::input()
  {
    BOOST_FOREACH(Object *obj, active_objects) {
      obj->input();
    }
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
