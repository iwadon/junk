#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "smf.hpp"
#ifdef HAVE_BOOST
#include <boost/foreach.hpp>
#endif
#ifdef HAVE_SDL_H
#include <SDL.h>
#endif
#include "instrument.hpp"
#include "logger.hpp"

/// コンストラクタ
SMF::SMF()
  : data_(NULL)
  , time_base_(48)
  , ticks_(0)
  , inst_(NULL)
  , tempo_(800000)
{
  set_ticks_add_();
}

/// デストラクタ
SMF::~SMF()
{
  BOOST_FOREACH(track_ptr_type t, tracks_) {
    delete t;
  }
  SDL_free(data_);
}

/**
 * @brief 再生中かどうかを返す
 *
 * @retval true  再生中です。
 * @retval false 再生していません。
 *
 * @code
 * if (smf.is_playing()) {
 *   // 再生中
 * } else {
 *   // 再生していない
 * }
 * @endcode
 */
bool SMF::is_playing() const
{
  bool result = false;
  for (std::vector<track_ptr_type>::const_iterator i = tracks_.begin(); i != tracks_.end(); ++i) {
    track_ptr_type t(*i);
    if (t->is_playing()) {
      result = true;
    }
  }
  return result;
}

/**
 * @brief ファイルからSMFデータを読み込む
 *
 * @param [in] filename ファイル名。
 *
 * @retval true  正常に読み込めました。
 * @retval false 処理中にエラーが起きました。
 *
 * @code
 * bool result = smf.load_file("sample.mid");
 * if (!result) {
 *   puts("sample.midを読み込めませんでした");
 * }
 * @endcode
 */
bool SMF::load_file(const SP &filename)
{
  SDL_RWops *ctx = SDL_RWFromFile(filename.data(), "rb");
  if (ctx == NULL) {
    SDL_ERROR("SDL_RWFromFile");
    return false;
  }
  size_t data_len_ = SDL_RWseek(ctx, 0, RW_SEEK_END);
  SDL_RWseek(ctx, 0, RW_SEEK_SET);
  void *p = SDL_malloc(data_len_);
  if (p == NULL) {
    SDL_ERROR("SDL_malloc");
    return false;
  }
  SDL_free(data_);
  data_ = reinterpret_cast<data_type *>(p);
  if (SDL_RWread(ctx, data_, data_len_, 1) != 1) {
    SDL_ERROR("SDL_RWread");
    return false;
  }
  if (SDL_RWclose(ctx) == -1) {
    SDL_ERROR("SDL_RWclose");
    return false;
  }
  return parse_data();
}

/**
 * @brief 再生を開始する
 *
 * @note 実際に再生したかどうかを確認するには SMF::is_playing() を使います。
 *
 * @sa SMF::is_playing
 * @sa SMF::stop
 *
 * @code
 * smf.play();
 * @endcode
 */
void SMF::play()
{
  for (std::vector<track_ptr_type>::iterator i = tracks_.begin(); i != tracks_.end(); ++i) {
    track_ptr_type t(*i);
    t->play();
  }
}

/**
 * @brief SMFデータの再生状態を更新する
 *
 * SMFデータの再生処理を随時更新するために、この関数を定期的に呼びます。
 *
 * @note SMF::play()を呼び出しただけではSMFデータの再生は始まりません。
 *       必ずこの関数を呼び出してください。
 *
 * @bug 現在の実装では秒間60回呼ばれることを想定しています。
 *
 * @code
 * smf.update();
 * @endcode
 */
void SMF::update()
{
  ticks_ += ticks_add_;
  int ticks_i = ticks_;
  ticks_ -= ticks_i;
  for (int i = 0; i < ticks_i; ++i) {
    for (std::vector<track_ptr_type>::iterator i = tracks_.begin(); i != tracks_.end(); ++i) {
      track_ptr_type t(*i);
      t->update();
    }
  }
  if (inst_ != NULL) {
    inst_->update();
  }
}

#define VALUE16(addr) (((addr)[0] << 8) | (addr)[1])
#define VALUE32(addr) (VALUE16((addr)) | VALUE16((addr) + 2))

bool SMF::parse_data()
{
  INFO("Parsing data...");
  if (memcmp(data_ + 0, "\x4d\x54\x68\x64\x00\x00\x00\x06", 8) != 0) {
    ERROR("Not SMF format");
    return false;
  }
  uint16_t format = VALUE16(data_ + 8);
  INFO("format %u", format);
  uint16_t num_tracks = VALUE16(data_ + 10);
  INFO("%u track(s)", num_tracks);
  time_base_ = VALUE16(data_ + 12);
  if ((time_base_ & 0x8000) != 0) {
    ERROR("Not implemented for negative value of the time base");
    return false;
  }
  set_ticks_add_();
  data_type *p = data_ + 14;
  for (uint16_t i = 0; i < num_tracks; ++i) {
    track_ptr_type t(new SMFTrack(*this));
    size_t chunk_size = 8 + VALUE32(p + 4);
    if (!t->setup(reinterpret_cast<SMFTrack::data_type *>(p), chunk_size)) {
      ERROR("Error at Track %d", i + 1);
      return false;
    }
    tracks_.push_back(t);
    p += chunk_size;
  }
  return true;
}

#undef VALUE16
#undef VALUE32

/**
 * @brief テンポを設定する
 * @param [in] data テンポを示すデータ。SMFのテンポ設定(Set Tempo)イベントで得られる「四分音符の長さをマイクロ秒で表した値」を想定しています。
 *
 * @code
 * static const uint8_t tempo[3] = {0x07, 0xa1, 0x20}; // BPM = 120
 * smf.set_tempo(tempo);
 * @endcode
 */
void SMF::set_tempo(const uint8_t *data)
{
  tempo_ = (data[0] << 16) | (data[1] << 8) | data[2];
  set_ticks_add_();
}

void SMF::set_ticks_add_()
{
  ticks_add_ = (1000000.0f * time_base_) / (tempo_ * 60);
}

/**
 * @brief 再生結果を波形データとして出力する
 *
 * @param [out] buf 波形データの出力先。
 * @param [in]  len 波形データの出力先の長さ。バイト単位で指定します。
 *
 * @retval true  波形データを出力しました。
 * @retval false Instrumentオブジェクトが未指定のため、波形データを出力しませんでした。
 *
 * @sa SMFTrack::mix_audio
 * @sa Instrument::mix_audio
 *
 * @code
 * char buf[2048];
 * size_t len = sizeof buf;
 * if (smf.mix_audio(buf, len)) {
 *   // bufに波形データがlenバイト出力された
 * } else {
 *   // 波形データは出力されなかった。
 * }
 * @endcode
 */
bool SMF::mix_audio(uint8_t *buf, const size_t len)
{
  if (inst_ != NULL) {
    return inst_->mix_audio(buf, len);
  } else {
    return false;
  }
}

/**
 * @brief オブジェクトの内容を示す文字列を返す
 *
 * @return オブジェクトの内容を示す文字列。
 *
 * @code
 * smf.inspect();
 * @endcode
 */
std::string SMF::inspect() const
{
  if (inst_ != NULL) {
    return inst_->inspect();
  } else {
    std::string s("SMF::inspect: inst_ is NULL");
    return s;
  }
}
