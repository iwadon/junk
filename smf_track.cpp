#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "smf_track.hpp"
#include "channel.hpp"
#include "instrument.hpp"
#include "smf.hpp"
#include "variable_length_value.hpp"

#ifdef SMF_TRACK_DEBUG
#include "logger.hpp"
#define SET_STATE(s) set_state(s)
#else
#define SET_STATE(s) state_ = (s)
#endif

static const SMFTrack::data_type MTHD[4] = {'M', 'T', 'h', 'd'};
static const SMFTrack::data_type MTRK[4] = {'M', 'T', 'r', 'k'};

SMFTrack::SMFTrack(SMF &smf)
  : smf_(smf)
  , data_(NULL)
  , data_end_(NULL)
  , data_cur_(NULL)
  , wait_time_(0)
  , state_(STATE_NONE)
  , flag_(0)
{
}

void SMFTrack::update()
{
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
    data_type data = *data_cur_++;
    Channel &ch = smf_.instrument().channel(data & 0x0f);
#ifdef ENABLE_RUNNING_STATUS
  retry:
#endif
    switch (static_cast<unsigned char>(data)) {
#ifdef ENABLE_RUNNING_STATUS
    case 0x00 ... 0x7f:		// Running Status
      data = prev_status_byte;
      goto retry;
      //break;
#endif
    case 0x80 ... 0x8f:		// 8n kk vv   Note Off
      {
	data_type kk = *data_cur_++;
	assert(data_cur_ <= data_end_);
	data_type vv = *data_cur_++;
	assert(data_cur_ <= data_end_);
	ch.note_off(kk, vv);
      }
      break;
    case 0x90 ... 0x9f:		// 9n kk vv   Note On
      {
	data_type kk = *data_cur_++;
	assert(data_cur_ <= data_end_);
	data_type vv = *data_cur_++;
	assert(data_cur_ <= data_end_);
	ch.note_on(kk, vv);
      }
      break;
    case 0xa0 ... 0xaf:		// An kk vv   Polyphonic Pressure
      {
	data_type kk = *data_cur_++;
	assert(data_cur_ <= data_end_);
	data_type vv = *data_cur_++;
	assert(data_cur_ <= data_end_);
	ch.polyphonic_pressure(kk, vv);
      }
      break;
    case 0xb0 ... 0xbf:		// Bn cc vv   Control Change
      {
	data_type cc = *data_cur_++;
	assert(data_cur_ <= data_end_);
	data_type vv = *data_cur_++;
	assert(data_cur_ <= data_end_);
	ch.control_change(cc, vv);
      }
      break;
    case 0xc0 ... 0xcf:		// Cn pp      Program Change
      {
	data_type pp = *data_cur_++;
	assert(data_cur_ <= data_end_);
	ch.program_change(pp);
      }
      break;
    case 0xd0 ... 0xdf:		// Dn vv      Channel Pressure
      {
	data_type vv = *data_cur_++;
	assert(data_cur_ <= data_end_);
	ch.channel_pressure(vv);
      }
      break;
    case 0xe0 ... 0xef:		// En ll mm   Pitch Bend
      {
	data_type ll = *data_cur_++;
	assert(data_cur_ <= data_end_);
	data_type mm = *data_cur_++;
	assert(data_cur_ <= data_end_);
	ch.pitch_bend_change(mm * 128 + ll - 8192);
      }
      break;
    case 0xf0:	       		// F0 ... F7  SysEx
      {
	VariableLengthValue delta_time;
	VariableLengthValue::len_type vlv_len = delta_time.set_data(data_cur_, 0);
	data_cur_ += vlv_len + delta_time.value();
	assert(data_cur_ <= data_end_);
      }
    case 0xf7:			// F7 ...     SysEx
      {
	VariableLengthValue delta_time;
	VariableLengthValue::len_type vlv_len = delta_time.set_data(data_cur_, 0);
	data_cur_ += vlv_len + delta_time.value();
	assert(data_cur_ <= data_end_);
      }
      break;
    case 0xff:
      {
	data_type type = *data_cur_++;
	assert(data_cur_ <= data_end_);
	VariableLengthValue data_len;
	VariableLengthValue::len_type vlv_len = data_len.set_data(data_cur_, 0);
	data_cur_ += vlv_len;
	assert(data_cur_ <= data_end_);
	switch (type) {
	case 0x01: // FF 01 len text		Text Event
	case 0x02: // FF 02 len text		Copyright Notice
	case 0x03: // FF 03 len text		Sequence/Track Name
	case 0x04: // FF 04 len text		Instrument Name
	case 0x05: // FF 05 len text		Lyric
	case 0x06: // FF 06 len text		Marker
	case 0x07: // FF 07 len text		Cue Point
	case 0x09: // FF 09 len text		Device Name
	case 0x20: // FF 20 01 cc		MIDI Channel Prefix
	case 0x54: // FF 54 05 hr mn se fr ff	SMPTE Offset
	case 0x58: // FF 58 04 nn dd cc bb	Time Signature
	case 0x59: // FF 59 02 sf mi		Key Signature
	case 0x7f: // FF 7F len data		Sequencer Specific Meta-Event
	  // not implemented
	  data_cur_ += data_len.value();
	  assert(data_cur_ <= data_end_);
	  break;
	case 0x2f: // FF 2F 00			End of Track
#ifdef SMF_TRACK_DEBUG
	  if (data_len.value() > 0) {
	    WARN("End of Track event is too long: %u > 0", data_len.value());
	  }
#endif
	  data_cur_ += data_len.value();
	  stop();
	  break;
	case 0x51: // FF 51 03 tttttt		Set Tempo(in microseconds per MIDI quarter-note)
	  smf_.set_tempo(reinterpret_cast<const uint8_t *>(data_cur_));
	  data_cur_ += data_len.value();
	  assert(data_cur_ <= data_end_);
	  break;
	default:
	  // unsupported meta-events
#ifdef SMF_TRACK_DEBUG
	  INFO("Unimplemented meta events: type=%02x, len=%u", static_cast<uint8_t>(type), data_len.value());
#endif
	  data_cur_ += data_len.value();
	  assert(data_cur_ <= data_end_);
	  break;
	}
      }
      break;
    default:
      // unsupported events
#ifdef SMF_TRACK_DEBUG
      INFO("Unimplemented events: %02x", static_cast<uint8_t>(data));
#endif
      break;
    }
#ifdef ENABLE_RUNNING_STATUS
    prev_status_byte = data;
#endif
    if (!is_playing()) {
      break;
    }
    update_wait_time();
  } while (wait_time_ == 0);
}

bool SMFTrack::setup(const data_type *data, const size_t size)
{
  if (size < 8) {
#ifdef SMF_TRACK_DEBUG
    ERROR("Too short data");
#endif
    return false;
  }
  if (memcmp(data, "MTrk", 4) != 0) {
#ifdef SMF_TRACK_DEBUG
    ERROR("Not MTrk data");
#endif
    return false;
  }
  const uint8_t *d = reinterpret_cast<const uint8_t *>(data);
  size_t data_size = d[4] << 24 | d[5] << 16 | d[6] << 8 | d[7];
  if (data_size != size - 8) {
#ifdef SMF_TRACK_DEBUG
    ERROR("mismatch data size: %zu %zu %02x%02x%02x%02x", data_size, size - 8, d[4], d[5], d[6], d[7]);
#endif
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
}

void SMFTrack::stop()
{
  resume();
  data_ = NULL;
  SET_STATE(STATE_STOPPED);
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
  wait_time_ += delta_time.value();
}

#ifdef SMF_TRACK_DEBUG

static const char *state_string[SMFTrack::NUM_STATES] = {
  "NONE",
  "INITIALIZED",
  "PLAYING",
  "STOPPED",
};

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
