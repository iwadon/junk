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

int Sound::Play(int label)
{
  return RESULT_OK;
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
}

void Sound::StopAudio()
{
  SDL_PauseAudio(1);
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

static const char SND_ID[4] = {'S', 'N', 'D', 0};

struct SND_V0_BASE
{
  // Header
  char format_signature[4];
  uint32_t format_version;
  uint32_t file_size;
  uint32_t file_id;
  // Labels
  uint32_t num_labels;
  uint32_t label_offsets[0];
};

struct SND_V0_LABEL_BASE
{
  uint8_t type;
  uint8_t category;
  uint8_t file_id;
  uint8_t group_id;
};

struct SND_V0_LABEL_WAV : public SND_V0_LABEL_BASE
{
  uint8_t data[0];
};

static bool ReadFile(void *&buf, size_t &size, const SP &filename)
{
  SDL_RWops *f = SDL_RWFromFile(filename.c_str(), "rb");
  if (f == NULL) {
    SDL_ERROR(SDL_RWFromFile);
    return false;
  }

  size_t len = SDL_RWseek(f, 0, RW_SEEK_END);
  SDL_RWseek(f, 0, RW_SEEK_SET);

  void *p = SDL_malloc(len);
  if (p == NULL) {
    SDL_ERROR(SDL_malloc);
    SDL_RWclose(f);
    return false;
  }

  if (SDL_RWread(f, p, len, 1) != 1) {
    SDL_ERROR(SDL_RWread);
    SDL_free(p);
    SDL_RWclose(f);
    return false;
  }

  SDL_RWclose(f);

  buf = p;
  size = size;
  return true;
}

bool Sound::LoadSndFile(const SP &filename)
{
  void *buf;
  size_t size;
  if (!ReadFile(buf, size, filename)) {
    return false;
  }

  const char *p = reinterpret_cast<const char *>(buf);
  if (memcmp(p, SND_ID, sizeof SND_ID) != 0) {
    LOG_ERROR("not SND format: %s", filename.c_str());
    return false;
  }

  const SND_V0_BASE *base = reinterpret_cast<SND_V0_BASE *>(buf);
  LOG_INFO("Loaded SND file: %s", filename.c_str());
  LOG_INFO("  Format Version: %u", base->format_version);
  LOG_INFO("  File Size: %u", base->file_size);
  LOG_INFO("  File ID: 0x%08x", base->file_id);
  for (uint32_t i = 0; i < base->num_labels; ++i) {
    const SND_V0_LABEL_BASE *label = reinterpret_cast<const SND_V0_LABEL_BASE *>(reinterpret_cast<const char *>(buf) + base->label_offsets[i]);
    LOG_INFO("  Label 0x%08x:", i);
    LOG_INFO("    Type: %u", label->type);
    LOG_INFO("    Category: %u", label->category);
    LOG_INFO("    File ID: %u", label->file_id);
    LOG_INFO("    Group ID: %u", label->group_id);
  }

  SDL_free(buf);
  return true;
}
