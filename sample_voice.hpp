#ifndef SAMPLE_VOICE_HPP_INCLUDED
#define SAMPLE_VOICE_HPP_INCLUDED 1

#include "voice_base.hpp"
#include <boost/cstdint.hpp>

class SampleVoice : public VoiceBase
{
public:
  virtual void MixAudio(void *buf, int len);
};

class WavVoice : public SampleVoice
{
public:
  void Update();
  void MixAudio(void *buf, int len);
  void SetData(uint8_t *data);
private:
};

#endif // !defined(SAMPLE_VOICE_HPP_INCLUDED)
