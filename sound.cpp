#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sound.hpp"
#include <SDL.h>
#include "sdl_logger.hpp"

Sound::Sound()
{
}

Sound::~Sound()
{
  Finalize();
}

int Sound::Initialize()
{
  if (!InitializeAudio()) {
    return RESULT_ERROR;
  }

  return RESULT_OK;
}

void Sound::Finalize()
{
  FinalizeAudio();
}

void Sound::Update()
{
}

int Sound::StartServer()
{
  return RESULT_OK;
}

int Sound::StopServer()
{
  return RESULT_OK;
}

bool Sound::InitializeAudio()
{
  SDL_AudioSpec spec;
  memset(&spec, 0, sizeof spec);
  spec.freq = 48000;
  spec.format = AUDIO_S16LSB;
  spec.channels = 1;
  spec.samples = 512;
  spec.callback = &Sound::AudioCallback;
  spec.userdata = this;
  if (SDL_OpenAudio(&spec, &audio_spec_) < 0) {
    SDL_ERROR(SDL_OpenAudio);
    return false;
  }
  LogAudioDrivers();
  LogAudioSpec();
  return true;
}

void Sound::FinalizeAudio()
{
  StopAudio();
  SDL_CloseAudio();
}

void Sound::StartAudio()
{
  SDL_PauseAudio(0);
  LOG_INFO("Start audio");
}

void Sound::StopAudio()
{
  SDL_PauseAudio(1);
  LOG_INFO("Stop audio");
}

void Sound::LogAudioDrivers()
{
  LOG_INFO("Audio Drivers:");
  int num_audio_drivers = SDL_GetNumAudioDrivers();
  const char *current_audio_driver = SDL_GetCurrentAudioDriver();
  for (int i = 0; i < num_audio_drivers; ++i) {
    const char *audio_driver = SDL_GetAudioDriver(i);
    LOG_INFO("  %d: %s%s", i, audio_driver, !strcmp(audio_driver, current_audio_driver) ? " (current)" : "");
  }
}

void Sound::LogAudioSpec()
{
  LOG_INFO("Audio Spec:");
  LOG_INFO("  freq: %d", audio_spec_.freq);
  LOG_INFO("  format: %u (%s, %s, %s, %ubit)", audio_spec_.format,
       SDL_AUDIO_ISSIGNED(audio_spec_.format) ? "signed" : "unsigned",
       SDL_AUDIO_ISBIGENDIAN(audio_spec_.format) ? "big-endian" : "little-endian",
       SDL_AUDIO_ISFLOAT(audio_spec_.format) ? "float" : "integer",
       SDL_AUDIO_BITSIZE(audio_spec_.format));
  LOG_INFO("  channels: %u", audio_spec_.channels);
  LOG_INFO("  silence: %u", audio_spec_.silence);
  LOG_INFO("  samples: %u", audio_spec_.samples);
  LOG_INFO("  padding: %u", audio_spec_.padding);
  LOG_INFO("  size: %u", audio_spec_.size);
}

void Sound::AudioCallback(void *userdata, uint8_t *stream, int len)
{
  Sound *sound = reinterpret_cast<Sound *>(userdata);
  memset(stream, 0, len);
  sound->MixAudio(stream, len);
}

void Sound::MixAudio(void *buf, int len)
{
}

static const char HEADER_ID[4] = {'S', 'N', 'D', 0};

static bool ReadFile(void *&buf, size_t &size, const SP &filename)
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

bool Sound::LoadSndFile(const SP &filename)
{
  void *buf;
  size_t size;
  if (!ReadFile(buf, size, filename)) {
    return false;
  }
  const char *p = reinterpret_cast<const char *>(buf);
  if (memcmp(p, HEADER_ID, sizeof HEADER_ID) != 0) {
    LOG_ERROR("SNDファイルではありません: %s", filename.c_str());
    return false;
  }
  SDL_free(buf);
  return true;
}
