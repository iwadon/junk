#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sound.hpp"
#include <SDL.h>
#include "sdl_logger.hpp"
#include "sp.hpp"

static const char HEADER_ID[4] = {'S', 'N', 'D', 0};

static bool read_file(void *&buf, size_t &size, const SP &filename)
{
  void *p;
  size_t len;
  SDL_RWops *f = SDL_RWFromFile(filename.c_str(), "rb");
  if (f == NULL) {
    SDL_ERROR(SDL_RWFromFile);
    goto error;
  }
  len = SDL_RWseek(f, 0, RW_SEEK_END);
  SDL_RWseek(f, 0, RW_SEEK_SET);
  p = SDL_malloc(len);
  if (p == NULL) {
    SDL_ERROR(SDL_malloc);
    goto error;
  }
  if (SDL_RWread(f, p, len, 1) != 1) {
    SDL_ERROR(SDL_RWread);
    goto error;
  }
  if (SDL_RWclose(f) == -1) {
    SDL_ERROR(SDL_RWclose);
  }
  buf = p;
  size = size;
  return true;
 error:
  if (f != NULL) {
    if (SDL_RWclose(f) == -1) {
      SDL_ERROR(SDL_RWclose);
    }
  }
  return false;
}

bool Sound::load_file(const SP &filename)
{
  void *buf;
  size_t size;
  if (!read_file(buf, size, filename)) {
    return false;
  }
  const char *p = reinterpret_cast<const char *>(buf);
  if (memcmp(p, HEADER_ID, sizeof HEADER_ID) != 0) {
    ERROR("SNDファイルではありません: %s", filename.c_str());
    return false;
  }
  SDL_free(buf);
  return true;
}
