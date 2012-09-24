#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sample_voice.hpp"
#include "wav.hpp"

void WavVoice::Update()
{
}

void WavVoice::MixAudio(void *buf, int len)
{
  if (!SetupMixBuffer(len)) {
    return;
  }
  wav_.ReadSamples(MixBufferAddr(), len / 2);
  SDL_MixAudio(reinterpret_cast<uint8_t *>(buf), MixBufferAddr(), len, SDL_MIX_MAXVOLUME);
}

void WavVoice::SetData(const void *data, size_t len)
{
  wav_.ParseData(data, len);
}
