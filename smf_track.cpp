#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "smf_track.hpp"
#ifdef STDCXX_98_HEADERS
#include <cstring>
#endif
#include "logger.hpp"
#include "sp.hpp"
#include "variable_length_value.hpp"

#ifdef SMF_TRACK_DEBUG
#define SET_STATE(s) set_state(s)
#else
#define SET_STATE(s) state_ = (s)
#endif

static const SMFTrack::data_type MTHD[4] = {'M', 'T', 'h', 'd'};
static const SMFTrack::data_type MTRK[4] = {'M', 'T', 'r', 'k'};

SMFTrack::SMFTrack()
  : data_(NULL)
  , data_end_(NULL)
  , data_cur_(NULL)
  , wait_time_(0)
  , state_(STATE_NONE)
  , flag_(0)
{
}

void SMFTrack::update()
{
  //DEBUG("%s: %d %d", __PRETTY_FUNCTION__, is_playing(), is_paused());
  if (!is_playing() || is_paused()) {
    return;
  }
  if (wait_time_ > 0) {
    --wait_time_;
    if (wait_time_ > 0) {
      return;
    }
  }
  if (data_end_ <= data_cur_) {
    return;
  }
  do {
    data_type data = *data_cur_;
    //DEBUG("%p: data=%02x", this, static_cast<uint8_t>(data));
    switch (data) {
    case 0x00 ... 0x7f:
      // running status
      break;
    case 0x80 ... 0x8f:
      // note off
      DEBUG("%p: %2dch note of %d %d", this, (data & 0x0f) + 1, data_cur_[1], data_cur_[2]);
      data_cur_ += 3;
      break;
    case 0x90 ... 0x9f:
      // note on
      DEBUG("%p: %2dch note on %d %d", this, (data & 0x0f) + 1, data_cur_[1], data_cur_[2]);
      data_cur_ += 3;
      break;
    case 0xa0 ... 0xaf:
      // polyphonic pressure
      DEBUG("%p: %2dch polyphonic pressure %d %d", this, (data & 0x0f) + 1, data_cur_[1], data_cur_[2]);
      data_cur_ += 3;
      break;
    case 0xb0 ... 0xbf:
      // control change
      DEBUG("%p: control change %d %d", this, data_cur_[1], data_cur_[2]);
      data_cur_ += 3;
      break;
    case 0xc0 ... 0xcf:
      // program change
      DEBUG("%p: program change %d", this, data_cur_[1]);
      data_cur_ += 2;
      break;
    case 0xd0 ... 0xdf:
      // channel pressure
      DEBUG("%p: channel pressure %d", this, data_cur_[1]);
      data_cur_ += 2;
      break;
    case 0xe0 ... 0xef:
      // pitch bend
      DEBUG("%p: pitch bend %d", this, (data_cur_[2] * 128 + data_cur_[1]) - 8192);
      data_cur_ += 3;
      break;
    case 0xff:
      // meta event
      //DEBUG("%p:   meta event: %02x", this, static_cast<uint8_t>(data_cur_[1]));
      switch (data_cur_[1]) {
      case 0x03:
	// sequence name or track name
	{
	  std::string name(data_cur_ + 3, data_cur_[2]);
	  DEBUG("%p: track name = %s", this, name.c_str());
	}
	data_cur_ += 3 + data_cur_[2];
	break;
      case 0x09:
	// device name
	{
	  std::string name(data_cur_ + 3, data_cur_[2]);
	  DEBUG("%p: device name = %s", this, name.c_str());
	}
	data_cur_ += 3 + data_cur_[2];
	break;
      case 0x2f:
	// end of track
	INFO("%p: end of track", this);
	stop();
	break;
      case 0x51:
	// Tempo setting
	DEBUG("%p:     Tempo setting", this);
	data_cur_ += 2 + 1 + 3;
	break;
      case 0x54:
	// SMPTE offset
	DEBUG("%p:     SMPTE offset", this);
	data_cur_ += 2 + 1 + 5;
	break;
      case 0x58:
	DEBUG("%p:     Time signature", this);
	data_cur_ += 2 + 1 + 4;
	break;
      default:
	// unsupported
	DEBUG("%p:     unsupported", this);
	break;
      }
      break;
    default:
      // unsupported
      break;
    }
    if (!is_playing()) {
      break;
    }
    update_wait_time();
  } while (wait_time_ == 0);
}

bool SMFTrack::setup(const data_type *data, const size_t size)
{
  if (size < 8) {
    ERROR("Too short data");
    return false;
  }
  if (memcmp(data, "MTrk", 4) != 0) {
    ERROR("Not MTrk data");
    return false;
  }
  size_t data_size = data[4] << 24 | data[5] << 16 | data[6] << 8 | data[7];
  if (data_size > size - 8) {
    ERROR("Too large data");
    return false;
  }
  data_ = data + 8;
  data_end_ = data_ + data_size;
  data_cur_ = NULL;
  SET_STATE(STATE_INITIALIZED);
  return true;
}

void SMFTrack::play()
{
  if (data_ == NULL) {
    return;
  }
  data_cur_ = data_;
  SET_STATE(STATE_PLAYING);
  update_wait_time();
  INFO("%p: play track", this);
}

void SMFTrack::stop()
{
  resume();
  data_ = NULL;
  SET_STATE(STATE_STOPPED);
  INFO("%p: stop track", this);
}

void SMFTrack::pause()
{
  flag_ |= FLAG_PAUSED;
}

void SMFTrack::resume()
{
  flag_ &= ~FLAG_PAUSED;
}

bool SMFTrack::is_playing() const
{
  return state_ == STATE_PLAYING;
}

bool SMFTrack::is_paused() const
{
  return flag_ & FLAG_PAUSED;
}

void SMFTrack::update_wait_time()
{
  VariableLengthValue delta_time;
  VariableLengthValue::len_type vlv_len = delta_time.set_data(data_cur_, 0);
  data_cur_ += vlv_len;
  assert(data_cur_ <= data_end_);
  wait_time_ = delta_time.value();
}

static const char *state_string[] = {
  "NONE",
  "INITIALIZED",
  "PLAYING",
  "STOPPED",
};

#ifdef SMF_TRACK_DEBUG

std::string SMFTrack::inspect() const
{
  std::string s = "#<SMFTrack";
  s += " ";
  s += state_string[state_];
  if (is_paused()) {
    s += " PAUSED";
  }
  s += ">";
  return s;
}

void SMFTrack::set_state(const STATE new_state)
{
  state_ = new_state;
}

#endif	// defined(SMF_TRACK_DEBUG)
