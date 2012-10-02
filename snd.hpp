#ifndef SND_BASE_HPP_INCLUDED
#define SND_BASE_HPP_INCLUDED 1

struct SND_BASE
{
  char format_signature[4];
  uint32_t format_version;
  uint32_t file_size;
  uint32_t file_id;
};

#endif // !defined(SND_BASE_HPP_INCLUDED)
