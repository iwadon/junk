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

class SMF
{
public:
  typedef uint8_t data_type;
  typedef boost::shared_ptr<SMFTrack> track_ptr_type;
  SMF();
  ~SMF();
  bool load_file(const SP &filename);
private:
  data_type *data_;
  uint32_t delta_time_;
  std::vector<track_ptr_type> tracks_;
  bool parse_data();
};

#endif // !defined(SMF_HPP_INCLUDED)
