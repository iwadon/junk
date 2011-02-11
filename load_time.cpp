#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "load_time.hpp"
#include <cassert>
#include <SDL.h>
#ifdef HAVE_MACH_MACH_TIME_H
#include <mach/mach_time.h>
#endif
#include "font.hpp"

static const int BAR_WIDTH = 100;

static LoadTime::time_type get_time()
{
#ifdef HAVE_MACH_MACH_TIME_H
  return mach_absolute_time();
#else
  return SDL_GetTicks();
#endif
}

static LoadTime::time_type get_elapsed_time(LoadTime::time_type end, LoadTime::time_type start)
{
#ifdef HAVE_MACH_MACH_TIME_H
  uint64_t elapsed = end - start;
  static mach_timebase_info_data_t info = {0, 0};
  if (info.denom == 0) {
    mach_timebase_info(&info);
  }
  return elapsed * info.numer / info.denom;
#else
  return end - start;
#endif
}

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
  if (item->flags & Item::FLAG_ACTIVE) {
    item->flags |= Item::FLAG_DIRTY;
    item->start = get_time();
  }
}

void LoadTime::stop(const size_t no)
{
  assert(no < NUM_ITEMS);
  Item *item = &items_[no];
  if (item->flags & Item::FLAG_ACTIVE) {
    item->end = get_time();
    item->elapsed += get_elapsed_time(item->end, item->start);
  }
}

void LoadTime::flip()
{
  for (size_t i = 0; i < NUM_ITEMS; ++i) {
    Item *item = &items_[i];
    if (item->flags & Item::FLAG_DIRTY) {
      item->last_elapsed = item->elapsed;
      item->start = item->end = item->elapsed = 0;
      item->flags &= ~Item::FLAG_DIRTY;
    }
  }
}

LoadTime::time_type LoadTime::elapsed_time(const size_t no) const
{
  assert(no < NUM_ITEMS);
  const Item *item = &items_[no];
  return item->last_elapsed;
}

void LoadTime::set_color(const size_t no, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
{
  assert(no < NUM_ITEMS);
  Item *item = &items_[no];
  item->color[0] = r;
  item->color[1] = g;
  item->color[2] = b;
  item->color[3] = a;
}

void LoadTime::set_name(const size_t no, const char *name)
{
  assert(no < NUM_ITEMS);
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

  // bar bg
  int xx = x + 12 + 8 * 27 + 4 * 2;
  int w = BAR_WIDTH;
  SDL_Rect bar_bg_rect = {xx, y, w * 2, 12};
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x60);
  SDL_RenderFillRect(renderer, &bar_bg_rect);

  // measure
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0x80);
  SDL_RenderDrawLine(renderer, xx, y, xx, y + 12);
  SDL_RenderDrawLine(renderer, xx + w, y, xx + w, y + 12);
  SDL_RenderDrawLine(renderer, xx + w * 2, y, xx + w * 2, y + 12);

  // items bg
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x80);
  SDL_Rect items_bg_rect = {x, y, 8 * 27 + 4 * 2, (active_items_.size() + 1) * 8 + 2 * 2};
  SDL_RenderFillRect(renderer, &items_bg_rect);

  // items
  int yy = y + 2;
  int tyy = yy;
  time_type total = 0;
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
    float percent = item->last_elapsed * 100.0f / (TIME_BASE_SEC / 60.0f);
    font->draw_strf(x + 12, tyy + 0, "%-8s %7.3fms %6.2f%%", item->name, item->last_elapsed * 1.0f / TIME_BASE_MILLISEC, percent);
    tyy += 8;
    
    // bar
    int n = percent * 100.0f / BAR_WIDTH;
    SDL_Rect bar_rect = {xx, yy, n, 8};
    SDL_SetRenderDrawColor(renderer, item->color[0], item->color[1], item->color[2], item->color[3]);
    SDL_RenderFillRect(renderer, &bar_rect);
    xx += n;

    total += item->last_elapsed;
  }

  float percent = total * 100.0f / (TIME_BASE_SEC / 60.0f);
  font->draw_strf(x + 12, tyy, "Total    %7.3fms %6.2f%%", total * 1.0f / TIME_BASE_MILLISEC, percent);

  // blend mode
  SDL_SetRenderDrawBlendMode(renderer, prev_blend_mode);
}

void LoadTime::activate(const size_t no)
{
  assert(no < NUM_ITEMS);
  Item *item = &items_[no];
  std::list<Item *>::iterator i = std::find(active_items_.begin(), active_items_.end(), item);
  if (i == active_items_.end()) {
    active_items_.push_back(item);
    item->flags |= Item::FLAG_ACTIVE;
  }
}
