#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "wav.hpp"
#include <SDL.h>
#include "logger.hpp"
#include "sdl_logger.hpp"

namespace {

const char RIFF[4] = {'R', 'I', 'F', 'F'};
const char WAVE[4] = {'W', 'A', 'V', 'E'};

struct Header
{
  char riff[4];
  uint32_t len;
  char wave[4];
};

struct Chunk
{
  uint32_t id;
  uint32_t len;
};

struct Fmt
{
  uint16_t format_id;
  uint16_t num_channels;
  uint32_t sample_rate;
  uint32_t bytes_per_second;
  uint16_t block_size;
  uint16_t bits_per_sample;
};

} // unnamed namespace

bool Wav::LoadFile(const SP &filename)
{
  uint32_t len;

  SDL_RWops *f = SDL_RWFromFile(filename.c_str(), "rb");
  if (f == NULL) {
    SDL_ERROR("SDL_RWFromFile failed");
    return false;
  }

  Header header;
  if (SDL_RWread(f, &header, sizeof header, 1) != 1) {
    LOG_ERROR("WAV header not found in %s", filename.c_str());
    goto error;
  }
  if (memcmp(header.riff, RIFF, 4) != 0 || memcmp(header.wave, WAVE, 4) != 0) {
    LOG_ERROR("%s is not WAV format", filename.c_str());
    goto error;
  }

  len = header.len - sizeof WAVE;
  while (len > 0) {
    Chunk chunk;
    if (SDL_RWread(f, &chunk, sizeof chunk, 1) != 1) {
      LOG_ERROR("Chunk header not found in %s", filename.c_str());
      goto error;
    }
    len -= sizeof chunk;
    switch (chunk.id) {
    case 0x20746d66:		// "fmt "
      {
	Fmt fmt;
	if (SDL_RWread(f, &fmt, sizeof fmt, 1) != 1) {
	  LOG_ERROR("Fmt chunk not found in %s", filename.c_str());
	  goto error;
	}
#if 0
	LOG_INFO("Fmt chunk:");
	LOG_INFO("  format_id: 0x%04x", fmt.format_id);
	LOG_INFO("  num_channels: %u", fmt.num_channels);
	LOG_INFO("  sample_rate: %u", fmt.sample_rate);
	LOG_INFO("  bytes_per_second: %u", fmt.bytes_per_second);
	LOG_INFO("  block_size: %u", fmt.block_size);
	LOG_INFO("  bits_per_sample: %u", fmt.bits_per_sample);
#endif
	if (fmt.format_id != 1) {
	  LOG_ERROR("%s is unsupported id %d, but supported Raw PCM format only", filename.c_str(), fmt.format_id);
	  goto error;
	}
	if (chunk.len > sizeof fmt) {
	  uint16_t ex_len;
	  if (SDL_RWread(f, &ex_len, sizeof ex_len, 1) != 1) {
	    LOG_ERROR("Extra part not found in %s", filename.c_str());
	    goto error;
	  }
	  if (ex_len > 0) {
	    SDL_RWseek(f, ex_len, RW_SEEK_CUR);
	  }
	}
      }
      break;
    case 0x61746164:		// "data"
      SDL_RWseek(f, chunk.len, RW_SEEK_CUR);
      break;
    default:
      SDL_RWseek(f, chunk.len, RW_SEEK_CUR);
      break;
    }
    len -= chunk.len;
    if (chunk.len & 1) {
      SDL_RWseek(f, 1, RW_SEEK_CUR);
      --len;
    }
  }

  SDL_RWclose(f);
  return true;

 error:
  SDL_RWclose(f);
  return false;
}
