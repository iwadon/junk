#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "smf.hpp"
#ifdef HAVE_SDL_H
#include <SDL.h>
#endif
#include "logger.hpp"

SMF::SMF()
  : data_(NULL)
{
}

SMF::~SMF()
{
  SDL_free(data_);
}

bool SMF::is_playing() const
{
  bool result = false;
  for (std::vector<track_ptr_type>::const_iterator i = tracks_.begin(); i != tracks_.end(); ++i) {
    track_ptr_type t(*i);
    if (t->is_playing()) {
      result = true;
    }
  }
  return result;
}

bool SMF::load_file(const SP &filename)
{
  SDL_RWops *ctx = SDL_RWFromFile(filename.data(), "rb");
  if (ctx == NULL) {
    ERROR("SDL_RWFromFile() failed: %s", SDL_GetError());
    return false;
  }
  size_t data_len_ = SDL_RWseek(ctx, 0, RW_SEEK_END);
  SDL_RWseek(ctx, 0, RW_SEEK_SET);
  void *p = SDL_malloc(data_len_);
  if (p == NULL) {
    ERROR("SDL_malloc() failed: %s", SDL_GetError());
    return false;
  }
  SDL_free(data_);
  data_ = reinterpret_cast<data_type *>(p);
  if (SDL_RWread(ctx, data_, data_len_, 1) != 1) {
    ERROR("SDL_RWread() failed: %s", SDL_GetError());
    return false;
  }
  if (SDL_RWclose(ctx) == -1) {
    ERROR("SDL_RWclose() failed: %s", SDL_GetError());
    return false;
  }
  return parse_data();
}

void SMF::play()
{
  for (std::vector<track_ptr_type>::iterator i = tracks_.begin(); i != tracks_.end(); ++i) {
    track_ptr_type t(*i);
    t->play();
  }
}

void SMF::update()
{
  for (std::vector<track_ptr_type>::iterator i = tracks_.begin(); i != tracks_.end(); ++i) {
    track_ptr_type t(*i);
    t->update();
  }
}

#define VALUE16(addr) (((addr)[0] << 8) | (addr)[1])
#define VALUE32(addr) (VALUE16((addr)) | VALUE16((addr) + 2))

bool SMF::parse_data()
{
  INFO("Parsing data...");
  if (memcmp(data_ + 0, "\x4d\x54\x68\x64\x00\x00\x00\x06", 8) != 0) {
    ERROR("Not SMF format");
    return false;
  }
  uint16_t format = VALUE16(data_ + 8);
  uint16_t num_tracks = VALUE16(data_ + 10);
  uint16_t delta_time_ = VALUE16(data_ + 12);
  if ((delta_time_ & 0x8000) != 0) {
    ERROR("Not implemented for negative value of delta time");
    return false;
  }
  data_type *p = data_ + 14;
  for (uint16_t i = 0; i < num_tracks; ++i) {
    track_ptr_type t(new SMFTrack);
    size_t chunk_size = 8 + VALUE32(p + 4);
    if (!t->setup(reinterpret_cast<SMFTrack::data_type *>(p), chunk_size)) {
      ERROR("Error at Track %d", i + 1);
      return false;
    }
    tracks_.push_back(t);
    p += chunk_size;
  }
  return true;
}

#undef VALUE16
#undef VALUE32
