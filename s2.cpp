#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "logger.hpp"
#include "point_2d.hpp"
#include "sdl_app.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include "vector_2d.hpp"
#include <list>
#include <memory>
#include <SDL.h>
#ifdef ENABLE_OPENGL
#include <SDL_opengl.h>
#endif

#define SHOW_WINDOW_AFTER_INITIALIZED

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
    virtual void input(SDLApp &/*app*/) {}
    virtual void move() {}
    virtual void update();
    virtual void draw(SDLApp &app) {}
  protected:
    Point2D pos_;
    Vector2D spd_;
    Vector2D acc_;
    float rot_;
    float scale_;
  };

  class DemoBox : public Object
  {
  public:
    DemoBox(SDL_Renderer *renderer);
    void initialize();
    void move();
    void draw(SDLApp &app);
  private:
    std::shared_ptr<Sprite> sprite_;
  };

  class MyShip : public Object
  {
  public:
    void initialize();
    void input(SDLApp &app);
    void move();
    void draw(SDLApp &app);
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

  DemoBox::DemoBox(SDL_Renderer *renderer)
    : sprite_(new Sprite(renderer))
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

  void DemoBox::draw(SDLApp &app)
  {
    sprite_->pos = pos_;
    sprite_->rot = rot_;
    sprite_->scale = scale_;
    sprite_->draw();
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

  void MyShip::input(SDLApp &app)
  {
    acc_.x = 0;
    acc_.y = 0;
    if (app.pad()->button & PAD_BUTTON_U) {
      acc_.y = -0.1;
    }
    if (app.pad()->button & PAD_BUTTON_D) {
      acc_.y = 0.1;
    }
    if (app.pad()->button & PAD_BUTTON_L) {
      acc_.x = -0.1;
    }
    if (app.pad()->button & PAD_BUTTON_R) {
      acc_.x = 0.1;
    }
  }

  void MyShip::move()
  {
    rot_ += 1.0f;
  }

  void MyShip::draw(SDLApp &app)
  {
#ifdef ENABLE_OPENGL
    glPushMatrix();
    glTranslatef(pos_.x, pos_.y, 0.0f);
    glRotatef(rot_, 0.0f, 0.0f, 1.0f);
    glScalef(scale_, scale_, 1.0f);
    SDL_Rect rect_o;
    rect_o.x = -MYSHIP_W / 2;
    rect_o.y = -MYSHIP_H / 2;
    rect_o.w = MYSHIP_W;
    rect_o.h = MYSHIP_H;
    SDL_Rect rect_i;
    rect_i.x = -MYSHIP_W / 2 + 1;
    rect_i.y = -MYSHIP_H / 2 + 1;
    rect_i.w = MYSHIP_W - 2;
    rect_i.h = MYSHIP_H - 2;
    SDL_SetRenderDrawColor(app.renderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(app.renderer(), &rect_o);
    SDL_SetRenderDrawColor(app.renderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(app.renderer(), &rect_i);
    glPopMatrix();
#endif
  }

  App::App()
    : SDLApp("s2")
  {
  }

  bool App::initialize(int /*argc*/, char */*argv*/[])
  {
    for (size_t i = 0; i < OBJ_NUM; ++i) {
      Object *obj = new DemoBox(renderer());
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
    for(auto obj: active_objects) {
      obj->input(*this);
    }
  }

  void App::move()
  {
    for (auto obj: active_objects) {
      obj->move();
    }
  }

  void App::update()
  {
    for (auto obj: active_objects) {
      obj->update();
    }
  }

  void App::draw()
  {
    for (auto obj: active_objects) {
      obj->draw(*this);
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
