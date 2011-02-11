#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "load_time.hpp"
#include <cassert>
#include <SDL.h>
#include "font.hpp"

LoadTime::LoadTime()
{
  for (size_t i = 0; i < NUM_ITEMS; ++i) {
    Item *item = &items_[i];
    memset(item, 0, sizeof *item);
    item->color[0] = (i & 1) ? 0xff : 0xaf;
    item->color[1] = (i & 2) ? 0xff : 0xaf;
    item->color[2] = (i & 4) ? 0xff : 0xaf;
    item->color[3] = 0xff;
    item->name = strdup("UNKNOWN");
  }
}

LoadTime::~LoadTime()
{
  for (size_t i = 0; i < NUM_ITEMS; ++i) {
    Item *item = &items_[i];
    free(item->name);
  }
}

void LoadTime::start(const size_t no)
{
  assert(no < NUM_ITEMS);
  Item *item = &items_[no];
  item->start = SDL_GetTicks();
  active_items_.push_back(item);
}

void LoadTime::stop(const size_t no)
{
  assert(no < NUM_ITEMS);
  Item *item = &items_[no];
  if (item->is_running()) {
    item->end = SDL_GetTicks();
  }
}

void LoadTime::flip()
{
  for (std::list<Item *>::iterator i = active_items_.begin(); i != active_items_.end(); ++i) {
    Item *item = *i;
    item->elapsed = item->end - item->start;
    item->start = item->end = 0;
  }
  active_items_.clear();
}

LoadTime::time_type LoadTime::elapsed_time(const size_t no) const
{
  const Item *item = &items_[no];
  return item->elapsed;
}

void LoadTime::set_color(const size_t no, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
{
  Item *item = &items_[no];
  item->color[0] = r;
  item->color[1] = g;
  item->color[2] = b;
  item->color[3] = a;
}

void LoadTime::set_name(const size_t no, const char *name)
{
  Item *item = &items_[no];
  free(item->name);
  item->name = strdup(name);
}

void LoadTime::draw(Font *font, const int x, const int y) const
{
  assert(font != NULL);
  SDL_Renderer *renderer = font->renderer();
  assert(renderer != NULL);

  // blend mode
  SDL_BlendMode prev_blend_mode;
  SDL_GetRenderDrawBlendMode(renderer, &prev_blend_mode);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  // measure
  int xx = x + 160;
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0x80);
  SDL_RenderDrawLine(renderer, xx, y, xx, y + 12);
  int w = 16 * 100 * 1000 / (1000 * 1000 / 60);
  SDL_RenderDrawLine(renderer, xx + w, y, xx + w, y + 12);
  w *= 2;
  SDL_RenderDrawLine(renderer, xx + w, y, xx + w, y + 12);

  // items bg
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x80);
  SDL_Rect items_bg_rect = {x, y, 8 * 18 + 4 * 2, active_items_.size() * 8 + 2 * 2};
  SDL_RenderFillRect(renderer, &items_bg_rect);

  // items
  int yy = y + 2;
  int tyy = yy;
  for (std::list<Item *>::const_iterator i = active_items_.begin(); i != active_items_.end(); ++i) {
    const Item *item = *i;

    // color
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_Rect text_color_frame_rect = {x + 4, tyy + 0, 7, 7};
    SDL_RenderFillRect(renderer, &text_color_frame_rect);
    SDL_SetRenderDrawColor(renderer, item->color[0], item->color[1], item->color[2], item->color[3]);
    SDL_Rect text_color_rect = {x + 5, tyy + 1, 5, 5};
    SDL_RenderFillRect(renderer, &text_color_rect);

    // text
    font->draw_strf(x + 12, tyy + 0, "%-8s %3d %3d%%", item->name, item->elapsed, item->elapsed * 100 * 1000 / (1000 * 1000 / 60));
    tyy += 8;
    
    // bar
    int n = item->elapsed * 100 * 1000 / (1000 * 1000 / 60);
    SDL_Rect rect = {xx, yy, n, 8};
    SDL_SetRenderDrawColor(renderer, item->color[0], item->color[1], item->color[2], item->color[3]);
    SDL_RenderFillRect(renderer, &rect);
    xx += n;
  }

  // blend mode
  SDL_SetRenderDrawBlendMode(renderer, prev_blend_mode);
}
