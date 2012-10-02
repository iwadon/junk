#ifndef SAMPLE_VOICE_HPP_INCLUDED
#define SAMPLE_VOICE_HPP_INCLUDED 1

#include "voice_base.hpp"
#include <boost/cstdint.hpp>
#include "wav.hpp"

class SampleVoice : public VoiceBase
{
public:
  virtual void SetData(const void *data, size_t len) = 0;
};

class WavVoice : public SampleVoice
{
public:
  void Update();
  void MixAudio(void *buf, int len);
  void SetData(const void *data, size_t len);
private:
  Wav wav_;
};

#endif // !defined(SAMPLE_VOICE_HPP_INCLUDED)
