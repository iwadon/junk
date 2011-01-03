#ifndef SMF_HPP_INCLUDED
#define SMF_HPP_INCLUDED 1

#ifdef STDCXX_98_HEADERS
#include <vector>
#endif
#include "smf_track.hpp"
#include "sp.hpp"

class Instrument;

class SMF
{
public:
  typedef uint8_t data_type;
  typedef SMFTrack *track_ptr_type;
  SMF();
  ~SMF();
  bool load_file(const SP &filename);
  void play();
  void update();
  bool is_playing() const;
  Instrument &instrument() { return *inst_; }
  void set_instrument(Instrument *inst) { inst_ = inst; }
  uint32_t time_base() const { return time_base_; }
  void set_tempo(const uint8_t *data);
  bool mix_audio(uint8_t *buf, const size_t len);
  std::string inspect() const;
private:
  data_type *data_;
  uint32_t time_base_;
  float ticks_add_;
  float ticks_;
  std::vector<track_ptr_type> tracks_;
  Instrument *inst_;
  uint32_t tempo_;
  bool parse_data();
  void set_ticks_add_();
};

#endif // !defined(SMF_HPP_INCLUDED)
