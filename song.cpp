#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "song.hpp"
#include <SDL.h>
#include "instrument.hpp"
#include "sdl_logger.hpp"
#include "smf.hpp"

Song::Song()
  : smf_(NULL)
{
}

Song::~Song()
{
  delete smf_;
}

bool Song::load_file(const SP &filename)
{
  SDL_RWops *ctx = SDL_RWFromFile(filename.data(), "rb");
  if (ctx == NULL) {
    SDL_ERROR("SDL_RWFromFile");
    return false;
  }
  size_t len = SDL_RWseek(ctx, 0, RW_SEEK_END);
  SDL_RWseek(ctx, 0, RW_SEEK_SET);
  void *p = SDL_malloc(len);
  if (p == NULL) {
    SDL_ERROR("SDL_malloc");
    return false;
  }
  if (SDL_RWread(ctx, p, len, 1) != 1) {
    SDL_ERROR("SDL_RWread");
    return false;
  }
  if (SDL_RWclose(ctx) == -1) {
    SDL_ERROR("SDL_RWclose");
    return false;
  }
  smf_ = new SMF(*this);
  return smf_->set_data(p);
}

void Song::set_instrument(Instrument *inst)
{
  inst_ = inst;
}

/**
 * @brief データの再生状態を更新する
 *
 * データの再生処理を随時更新するために、この関数を定期的に呼びます。
 *
 * @note play()を呼び出しただけではデータの再生は始まりません。
 *       必ずこの関数を呼び出してください。
 *
 * @code
 * song.update();
 * @endcode
 */
void Song::update()
{
  if (smf_ != NULL) {
    smf_->update();
  }
  if (inst_ != NULL) {
    inst_->update();
  }
}

/**
 * @brief 再生を開始する
 *
 * @note 実際に再生したかどうかを確認するには SMF::is_playing() を使います。
 *
 * @sa is_playing
 * @sa stop
 *
 * @code
 * smf.play();
 * @endcode
 */
void Song::play()
{
  if (smf_ != NULL) {
    smf_->play();
  }
}

/**
 * @brief 再生中かどうかを返す
 *
 * @retval true  再生中です。
 * @retval false 再生していません。またはデータが設定されていません。
 *
 * @sa play
 * @sa set_data
 *
 * @code
 * if (song.is_playing()) {
 *   // 再生中
 * } else {
 *   // 再生していない
 * }
 * @endcode
 */
bool Song::is_playing() const
{
  if (smf_ != NULL) {
    return smf_->is_playing();
  } else {
    return false;
  }
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
 * @sa Instrument::mix_audio
 *
 * @code
 * char buf[2048];
x * size_t len = sizeof buf;
 * if (song.mix_audio(buf, len)) {
 *   // bufに波形データがlenバイト出力された
 * } else {
 *   // 波形データは出力されなかった。
 * }
 * @endcode
 */
bool Song::mix_audio(uint8_t *buf, const size_t len)
{
  if (inst_ != NULL) {
    return inst_->mix_audio(buf, len);
  } else {
    return false;
  }
}
