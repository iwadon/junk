#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "smf_track.hpp"
#ifdef STDCXX_98_HEADERS
#include <cstring>
#endif
#include "channel.hpp"
#include "instrument.hpp"
#include "logger.hpp"
#include "smf.hpp"
#include "sp.hpp"
#include "variable_length_value.hpp"

#ifdef SMF_TRACK_DEBUG
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
    data_type data = *data_cur_;
    Channel &ch = smf_.instrument().channel(data & 0x0f);
  retry:
    switch (data) {
    case 0x00 ... 0x7f:
      // Running Status
      data = prev_status_byte;
      --data_cur_;
      goto retry;
      //break;
    case 0x80 ... 0x8f:
      ch.note_off(data_cur_[1], data_cur_[2]);
      data_cur_ += 3;
      break;
    case 0x90 ... 0x9f:
      ch.note_on(data_cur_[1], data_cur_[2]);
      data_cur_ += 3;
      break;
    case 0xa0 ... 0xaf:
      ch.polyphonic_pressure(data_cur_[1], data_cur_[2]);
      data_cur_ += 3;
      break;
    case 0xb0 ... 0xbf:
      ch.control_change(data_cur_[1], data_cur_[2]);
      data_cur_ += 3;
      break;
    case 0xc0 ... 0xcf:
      ch.program_change(data_cur_[1]);
      data_cur_ += 2;
      break;
    case 0xd0 ... 0xdf:
      ch.channel_pressure(data_cur_[1]);
      data_cur_ += 2;
      break;
    case 0xe0 ... 0xef:
      ch.pitch_bend_change((data_cur_[2] * 128 + data_cur_[1]) - 8192);
      data_cur_ += 3;
      break;
    case 0xf0:
    case 0xf7:
      // SysEx event
      {
	VariableLengthValue delta_time;
	VariableLengthValue::len_type vlv_len = delta_time.set_data(data_cur_ + 1, 0);
	data_cur_ += vlv_len;
      }
      break;
    case 0xff:
      switch (data_cur_[1]) {
      case 0x01: // FF 01 len text		Text Event
      case 0x02: // FF 02 len text		Copyright Notice
      case 0x03: // FF 03 len text		Sequence/Track Name
      case 0x04: // FF 04 len text		Instrument Name
      case 0x05: // FF 05 len text		Lyric
      case 0x06: // FF 06 len text		Marker
      case 0x07: // FF 07 len text		Cue Point
      case 0x09: // FF 09 len text		Device Name
      case 0x20: // FF 20 01 cc			MIDI Channel Prefix
      case 0x54: // FF 54 05 hr mn se fr ff	SMPTE Offset
      case 0x58: // FF 58 04 nn dd cc bb	Time Signature
      case 0x59: // FF 59 02 sf mi		Key Signature
      case 0x7f: // FF 7F len data		Sequencer Specific Meta-Event
	// not implemented
	data_cur_ += 2 + 1 + data_cur_[2];
	break;
      case 0x2f: // FF 2F 00			End of Track
	stop();
	break;
      case 0x51: // FF 51 03 tttttt		Set Tempo(in microseconds per MIDI quarter-note)
	smf_.set_tempo(reinterpret_cast<const uint8_t *>(data_cur_) + 3);
	data_cur_ += 2 + 1 + 3;
	break;
      default:
	// unsupported meta-events
	INFO("Unimplemented meta events: %02x", static_cast<uint8_t>(data_cur_[1]));
	data_cur_ += 2 + 1 + data_cur_[2];
	break;
      }
      break;
    default:
      // unsupported events
      INFO("Unimplemented events: %02x", static_cast<uint8_t>(data));
      break;
    }
    prev_status_byte = data;
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
  const uint8_t *d = reinterpret_cast<const uint8_t *>(data);
  size_t data_size = d[4] << 24 | d[5] << 16 | d[6] << 8 | d[7];
  if (data_size > size - 8) {
    ERROR("Too large data: %zu %zu %02x%02x%02x%02x", data_size, size - 8);
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
