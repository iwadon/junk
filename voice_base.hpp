#ifndef VOICE_BASE_HPP_INCLUDED
#define VOICE_BASE_HPP_INCLUDED 1

class VoiceBase
{
public:
  VoiceBase() {}
  virtual ~VoiceBase() {}
  virtual void Update() = 0;
  virtual void MixAudio(void *buf, int len) = 0;
};

#endif // !defined(VOICE_BASE_HPP_INCLUDED)
