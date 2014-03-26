#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "load_time.hpp"
#include <algorithm>
#include <cassert>
#include <SDL.h>
#if defined(__APPLE__)
#include <mach/mach_time.h>
#elif defined(_MSC_VER)
#define strdup _strdup
#define vsnprintf vsnprintf_s
#endif
#include "font.hpp"

static const size_t ITEMS_WIDTH = 8 * 27 + 4 * 2;
static const size_t BAR_WIDTH = ITEMS_WIDTH / 2;

static LoadTime::time_type get_time()
{
#if defined(__APPLE__)
  return mach_absolute_time();
#else
  return SDL_GetPerformanceCounter();
#endif
}

LoadTime::time_type LoadTime::get_elapsed_time(LoadTime::time_type end, LoadTime::time_type start) const
{
#if defined(__APPLE__)
  uint64_t elapsed = end - start;
  static mach_timebase_info_data_t info = {0, 0};
  if (info.denom == 0) {
    mach_timebase_info(&info);
  }
  return elapsed * info.numer / info.denom;
#else
	time_type elapsed = end - start;
	return elapsed * TIME_BASE_SEC / freq_;
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
#ifndef __APPLE__
  freq_ = SDL_GetPerformanceFrequency();
#endif
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
  int items_height = (active_items_.size() + 1) * 8 + 2 * 2;
  int bar_x = x;
  int bar_y = y + items_height + 4;
  SDL_Rect bar_bg_rect = {bar_x, bar_y, BAR_WIDTH * 2, 12};
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x80);
  SDL_RenderFillRect(renderer, &bar_bg_rect);

  // bar measure
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0x80);
  SDL_RenderDrawLine(renderer, bar_x                , bar_y, bar_x                , bar_y + 12);
  SDL_RenderDrawLine(renderer, bar_x + BAR_WIDTH    , bar_y, bar_x + BAR_WIDTH    , bar_y + 12);
  SDL_RenderDrawLine(renderer, bar_x + BAR_WIDTH * 2, bar_y, bar_x + BAR_WIDTH * 2, bar_y + 12);

  // items bg
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x80);
  SDL_Rect items_bg_rect = {x, y, ITEMS_WIDTH, items_height};
  SDL_RenderFillRect(renderer, &items_bg_rect);

  // items
  int items_y = y + 2;
  time_type total = 0;
  for (std::list<Item *>::const_iterator i = active_items_.begin(); i != active_items_.end(); ++i) {
    const Item *item = *i;

    // color
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_Rect text_color_frame_rect = {x + 4, items_y + 0, 7, 7};
    SDL_RenderFillRect(renderer, &text_color_frame_rect);
    SDL_SetRenderDrawColor(renderer, item->color[0], item->color[1], item->color[2], item->color[3]);
    SDL_Rect text_color_rect = {x + 5, items_y + 1, 5, 5};
    SDL_RenderFillRect(renderer, &text_color_rect);

    // text
    float ratio = item->last_elapsed / (TIME_BASE_SEC / 60.0f);
    font->draw_strf(x + 12, items_y + 0, "%-8s %7.3fms %6.2f%%", item->name, static_cast<float>(item->last_elapsed) / TIME_BASE_MILLISEC, ratio * 100.0f);
    items_y += 8;

    // bar
    int bar_w = BAR_WIDTH * ratio;
    SDL_Rect bar_rect = {bar_x, bar_y + 2, bar_w, 8};
    SDL_SetRenderDrawColor(renderer, item->color[0], item->color[1], item->color[2], item->color[3]);
    SDL_RenderFillRect(renderer, &bar_rect);
    bar_x += bar_w;

    total += item->last_elapsed;
  }

  float ratio = total / (TIME_BASE_SEC / 60.0f);
  font->draw_strf(x + 12, items_y, "Total    %7.3fms %6.2f%%", static_cast<float>(total) / TIME_BASE_MILLISEC, ratio * 100.0f);

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
