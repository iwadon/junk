#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "wav.hpp"
#include <SDL.h>
#include "logger.hpp"
#include "sdl_logger.hpp"
#include <iostream>

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

Wav::Wav()
  : data(NULL)
  , len(0)
  , pos(0)
{
}

Wav::~Wav()
{
  free(data);
}

bool Wav::LoadFile(const SP &filename)
{
  SDL_RWops *f = SDL_RWFromFile(filename.c_str(), "rb");
  if (f == NULL) {
    SDL_ERROR("SDL_RWFromFile failed");
    return false;
  }

  bool ret = ParseData(f);

  SDL_RWclose(f);

  return ret;
}

bool Wav::ParseData(const void *data, size_t size)
{
  SDL_RWops *f = SDL_RWFromConstMem(data, size);
  if (f == NULL) {
    SDL_ERROR("SDL_RWFromConstMem failed");
    return false;
  }

  bool ret = ParseData(f);

  SDL_RWclose(f);

  return false;
}

bool Wav::ParseData(SDL_RWops *f)
{
  Header header;
  if (SDL_RWread(f, &header, sizeof header, 1) != 1) {
    //LOG_ERROR("WAV header not found in %s", filename.c_str());
    return false;
  }
  if (memcmp(header.riff, RIFF, 4) != 0 || memcmp(header.wave, WAVE, 4) != 0) {
    //LOG_ERROR("%s is not WAV format", filename.c_str());
    return false;
  }

  ssize_t rest = header.len - sizeof WAVE;
  while (rest > 0) {
    Chunk chunk;
    if (SDL_RWread(f, &chunk, sizeof chunk, 1) != 1) {
      //LOG_ERROR("Chunk header not found in %s", filename.c_str());
      return false;
    }
    rest -= sizeof chunk;
    switch (chunk.id) {
    case 0x20746d66:		// "fmt "
      {
	Fmt fmt;
	if (SDL_RWread(f, &fmt, sizeof fmt, 1) != 1) {
	  //LOG_ERROR("Fmt chunk not found in %s", filename.c_str());
	  return false;
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
	  //LOG_ERROR("%s is unsupported id %d, but supported Raw PCM format only", filename.c_str(), fmt.format_id);
	  return false;
	}
	if (chunk.len > sizeof fmt) {
	  uint16_t ex_len;
	  if (SDL_RWread(f, &ex_len, sizeof ex_len, 1) != 1) {
	    //LOG_ERROR("Extra part not found in %s", filename.c_str());
	    return false;
	  }
	  if (ex_len > 0) {
	    SDL_RWseek(f, ex_len, RW_SEEK_CUR);
	  }
	}
      }
      break;
    case 0x61746164:		// "data"
      len = chunk.len;
      data = malloc(len);
      SDL_RWread(f, data, len, 1);
      break;
    default:
      SDL_RWseek(f, chunk.len, RW_SEEK_CUR);
      break;
    }
    rest -= chunk.len;
    if (chunk.len & 1) {
      SDL_RWseek(f, 1, RW_SEEK_CUR);
      --rest;
    }
  }

  return true;
}

size_t Wav::ReadSamples(void *buf, size_t samples)
{
  //std::cout << "samples=" << samples << ", pos=" << pos << std::endl;
  size_t rest = len / sizeof (int16_t) - pos;	      // 残りサンプル数
  size_t n = std::min(rest, samples); // 読み出そうとするサンプル数
  const uint8_t *src_addr = reinterpret_cast<uint8_t *>(data) + pos * sizeof (int16_t); // 読み出すデータの先頭アドレス
  const size_t src_len = n * sizeof (int16_t);	// 読みだすデータの長さ(バイト単位)
  memcpy(buf, src_addr, src_len);
  pos += n;
  if (n < samples) {
    memset(reinterpret_cast<uint8_t *>(buf) + src_len * sizeof (int16_t), 0, (samples - n) * sizeof (int16_t));
  }
  return n;
}
