#ifndef VOICE_BASE_HPP_INCLUDED
#define VOICE_BASE_HPP_INCLUDED 1

#include <cstddef>
#include <cstdint>

class VoiceBase
{
public:
  VoiceBase() {}
  virtual ~VoiceBase() {}
  virtual void Update() = 0;
  virtual void MixAudio(void *buf, int len) = 0;
protected:
  bool SetupMixBuffer(size_t len);
  uint8_t *MixBufferAddr() { return mix_buf_.addr; }
private:
  struct MixBuffer
  {
    uint8_t *addr;
    size_t len;
    MixBuffer();
    ~MixBuffer();
    bool Prepare(size_t new_len);
  };
  MixBuffer mix_buf_;
};

#endif // !defined(VOICE_BASE_HPP_INCLUDED)
