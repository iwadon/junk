#ifndef AUDIO_STREAM_HPP_INCLUDED
#define AUDIO_STREAM_HPP_INCLUDED 1

#include <cstddef>

/// オーディオデータを読み出すためのストリーム
class AudioStream
{
public:
  virtual size_t read(void *buf, const size_t len, const float ratio) = 0;
};

#endif // !defined(AUDIO_STREAM_HPP_INCLUDED)
