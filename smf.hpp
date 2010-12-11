#ifndef SMF_HPP_INCLUDED
#define SMF_HPP_INCLUDED 1

#ifdef STDCXX_98_HEADERS
#include <vector>
#endif
#ifdef HAVE_BOOST
#include <boost/shared_ptr.hpp>
#endif
#include "smf_track.hpp"
#include "sp.hpp"

class Instrument;

class SMF
{
public:
  typedef uint8_t data_type;
  typedef boost::shared_ptr<SMFTrack> track_ptr_type;
  SMF();
  ~SMF();
  bool load_file(const SP &filename);
  void play();
  void update();
  bool is_playing() const;
  void set_instrument(Instrument *inst) { inst_ = inst; }
  uint32_t time_base() const { return time_base_; }
  void set_tempo(const uint8_t *data);
  float ticks_add() const { return ticks_add_; }
private:
  data_type *data_;
  uint32_t time_base_;
  float ticks_add_;
  std::vector<track_ptr_type> tracks_;
  Instrument *inst_;
  bool parse_data();
};

#endif // !defined(SMF_HPP_INCLUDED)
