#include <iostream>
#include <list>
#include <boost/foreach.hpp>
#include <boost/pool/object_pool.hpp>
#include <SDL.h>
#include "point.hpp"
#include "vector.hpp"

#define SHOW_WINDOW_AFTER_INITIALIZED

namespace game
{
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

  class App
  {
  public:
    ~App();
    int run(int argc, char *argv[]);
  private:
    SDL_Window *window_;
    bool done_;
    boost::object_pool<Object> objects;
    std::list<Object *> active_objects;
    bool initialize(int argc, char *argv[]);
    void finalize();
    void move();
    void update();
    void draw();
  };

  Object::Object()
  {
    pos_.x = (rand() * 1.0f / RAND_MAX) * 540 + 50;
    pos_.y = (rand() * 1.0f / RAND_MAX) * 860 + 50;
    spd_.x = (rand() * 1.0f / RAND_MAX) * 3;
    spd_.y = (rand() * 1.0f / RAND_MAX) * 3;
    acc_.x = 0.0f;
    acc_.y = 0.1f;
  }

  void Object::move()
  {
    if (pos_.y > 960 - 50) {
      pos_.y = 960 - 50;
      spd_.y = -spd_.y;
    }
    if (pos_.x < 0 + 50) {
      pos_.x = 0 + 50;
      spd_.x = -spd_.x;
    }
    if (pos_.x > 640 - 50) {
      pos_.x = 640 - 50;
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
    SDL_SetRenderDrawColor(0xf0, 0xf0, 0xf0, 0xff);
    SDL_Rect rect = {pos_.x - 50, pos_.y - 50, 100, 100};
    SDL_RenderFillRect(&rect);
  }

  App::~App()
  {
    finalize();
  }

  int App::run(int argc, char *argv[])
  {
    if (!initialize(argc, argv)) {
      return 1;
    }
#ifdef SHOW_WINDOW_AFTER_INITIALIZED
    draw();
    SDL_ShowWindow(window_);
#endif

    for (int i = 0; i < 10; ++i) {
      Object *obj = objects.construct();
      active_objects.push_back(obj);
    }

    done_ = false;
    while (!done_) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
	switch (event.type) {
	case SDL_QUIT:
	  done_ = true;
	  break;
	case SDL_WINDOWEVENT:
	  switch (event.window.event) {
	  case SDL_WINDOWEVENT_CLOSE:
	    done_ = true;
	    break;
	  }
	  break;
	}
      }
      move();
      update();
      draw();
      SDL_Delay(1000 / 60);
    }
    return 0;
  }

  bool App::initialize(int argc, char *argv[])
  {
    window_ = SDL_CreateWindow("s2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 960,
#ifdef SHOW_WINDOW_AFTER_INITIALIZED
			       0
#else
			       SDL_WINDOW_SHOWN
#endif
			       );
    if (window_ == NULL) {
      std::cerr << "ERROR: SDL_CreateWindow: " << SDL_GetError() << std::endl;
      return false;
    }
    if (SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTFLIP3) < 0) {
      std::cerr << "ERROR: SDL_CreateRenderer: " << SDL_GetError() << std::endl;
      return false;
    }
    return true;
  }

  void App::finalize()
  {
    SDL_Quit();
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
    SDL_SetRenderDrawColor(0x00, 0xa0, 0x00, 0xff);
    SDL_RenderClear();

    BOOST_FOREACH(Object *obj, active_objects) {
      obj->draw();
    }
    
    SDL_RenderPresent();
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
