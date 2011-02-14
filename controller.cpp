#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "controller.hpp"

const Controller::Data Controller::empty_data_ = {{0, 0, 0}};

void Controller::update(const SDL_Event &event)
{
  Data prev;
  Data now = {{0, 0, 0}};

  prev = latest_data();
  now.key.status = prev.key.status;

  switch (event.type) {
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      now.key.on |= 1 << 0;
      break;
    case SDLK_DOWN:
      now.key.on |= 1 << 1;
      break;
    case SDLK_LEFT:
      now.key.on |= 1 << 2;
      break;
    case SDLK_RIGHT:
      now.key.on |= 1 << 3;
      break;
    }
    break;
  case SDL_KEYUP:
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      now.key.off |= 1 << 0;
      break;
    case SDLK_DOWN:
      now.key.off |= 1 << 1;
      break;
    case SDLK_LEFT:
      now.key.off |= 1 << 2;
      break;
    case SDLK_RIGHT:
      now.key.off |= 1 << 3;
      break;
    }
    break;
  }
  now.key.status |= now.key.on;
  now.key.status &= ~now.key.off;
  data_list.push_back(now);
  updated_ = now.key != prev.key;
}
