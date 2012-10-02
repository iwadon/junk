#ifndef SND_V0_HPP_INCLUDED
#define SND_V0_HPP_INCLUDED 1

#include "snd.hpp"

struct SND_V0_BASE : public SND_BASE
{
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
  uint32_t len;
  uint8_t data[0];
};

#endif // !defined(SND_V0_HPP_INCLUDED)
