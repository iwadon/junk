#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sample_voice.hpp"
#include "wav.hpp"

void VoiceBase::MixAudio(void *buf, int len)
{
}

void SampleVoice::MixAudio(void *buf, int len)
{
  VoiceBase::MixAudio(buf, len);
}

void WavVoice::Update()
{
}

void WavVoice::MixAudio(void *buf, int len)
{
}

void WavVoice::SetData(const void *data, size_t len)
{
  wav_.ParseData(data, len);
  data_top_ = data_cur_ = static_cast<uint8_t *>(wav_.data);
  data_end_ = data_top_ + wav_.len;
}
