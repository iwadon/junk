#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "voice_base.hpp"
#include <SDL.h>
#include "sdl_logger.hpp"

bool VoiceBase::SetupMixBuffer(size_t len)
{
  return mix_buf_.Prepare(len);
}

VoiceBase::MixBuffer::MixBuffer()
  : addr(NULL)
  , len(0)
{
}

VoiceBase::MixBuffer::~MixBuffer()
{
  if (addr != NULL) {
    SDL_free(addr);
  }
}

bool VoiceBase::MixBuffer::Prepare(size_t new_len)
{
  if (new_len != len) {
    if (addr != NULL) {
      SDL_free(addr);
    }
    addr = reinterpret_cast<uint8_t *>(SDL_malloc(new_len));
    if (addr == NULL) {
      SDL_ERROR(SDL_malloc);
      len = 0;
      return false;
    }
    len = new_len;
  }
  return true;
}

