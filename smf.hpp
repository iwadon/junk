#ifndef SMF_HPP_INCLUDED
#define SMF_HPP_INCLUDED 1

#define SMF_DEBUG 1

#include <vector>
#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST)
#include <boost/cstdint.hpp>
#elif defined(HAVE_STDINT_H)
#include <stdint.h>
#endif
#include "sp.hpp"

class Instrument;
class SMFTrack;
class Song;

/**
 * @brief 標準MIDIファイル形式のシーケンスデータを扱うためのクラス
 *
 * @note 通常このクラスを直接使う必要はありません。
 *       実際のシーケンスデータの再生にはSongクラスを使います。
 *
 * @bug SMF::update()を1/60秒毎に呼び出さない場合、シーケンスデータが想定するテンポで再生されません。
 *
 * @sa Instrument
 * @sa SMFTrack
 * @sa Song
 */
class SMF
{
public:
  typedef uint8_t data_type;
  typedef SMFTrack *track_ptr_type;
  SMF(Song &);
  ~SMF();
  bool set_data(void *data);
  void play();
  void update();
  bool is_playing() const;
  Instrument *instrument();
  uint32_t time_base() const { return time_base_; }
  void set_tempo(const uint8_t *data);
  bool mix_audio(uint8_t *buf, const size_t len);
#ifdef SMF_DEBUG
  std::string inspect() const;
#endif
private:
  Song &song_;
  data_type *data_;
  uint32_t time_base_;
  float ticks_add_;
  float ticks_;
  std::vector<track_ptr_type> tracks_;
  uint32_t tempo_;
#ifdef SMF_DEBUG
  int format_;
  size_t num_tracks_;
#endif
  bool parse_data();
  void set_ticks_add_();
};

#endif // !defined(SMF_HPP_INCLUDED)
