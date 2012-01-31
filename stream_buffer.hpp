#ifndef STREAM_BUFFER_HPP_INCLUDED
#define STREAM_BUFFER_HPP_INCLUDED 1

#include <algorithm>
#include <cstddef>
#include <stdint.h>
#include <cstring>

class StreamBuffer
{
public:
  StreamBuffer(void *buf, const size_t size);
  size_t read_data(void *buf, const size_t size);
  template <typename T> T read_value();
  uint8_t read_uint8() { return read_value<uint8_t>(); }
  uint16_t read_uint16() { return read_value<uint16_t>(); }
  uint64_t read_uint32() { return read_value<uint32_t>(); }
  uint64_t read_uint64() { return read_value<uint64_t>(); }
  void write_data(const void *buf, const size_t buflen);
  template <typename T> void write_value(const T &value) { write_data(&value, sizeof (T)); }
  void write_uint8(const uint8_t value) { write_value(value); }
  void write_uint16(const uint16_t value) { write_value(value); }
  void write_uint32(const uint32_t value) { write_value(value); }
  void write_uint64(const uint64_t value) { write_value(value); }
  void reset() { cur_ = top_; }
  void resize(const size_t size) { bot_ = top_ + size; reset(); }
  size_t size() const { return cur_ - top_; }
  size_t rest() const { return is_rest() ? bot_ - cur_ : 0; }
  bool is_rest() const { return cur_ < bot_; }
  bool is_empty() const { return cur_ == top_; }
private:
  uint8_t *top_;
  uint8_t *bot_;
  uint8_t *cur_;
};

inline StreamBuffer::StreamBuffer(void *buf, size_t bytes)
  : top_(reinterpret_cast<uint8_t *>(buf))
  , bot_(top_ + bytes)
  , cur_(top_)
{
}

inline size_t StreamBuffer::read_data(void *buf, size_t buflen)
{
  size_t len = std::min(buflen, rest());
  memcpy(buf, cur_, len);
  cur_ += len;
  return len;
}

template <typename T>
inline T StreamBuffer::read_value()
{
  T value;
  if (read_data(&value, sizeof value) == sizeof value) {
    return value;
  } else {
    return 0;
  }
}

inline void StreamBuffer::write_data(const void *buf, const size_t buflen)
{
  size_t len = std::min(buflen, rest());
  memcpy(cur_, buf, len);
  cur_ += len;
}

#endif // !defined(STREAM_BUFFER_HPP_INCLUDED)
