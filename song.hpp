#ifndef SONG_HPP_INCLUDED
#define SONG_HPP_INCLUDED 1

#if defined(HAVE_TR1_CSTDINT)
#include <tr1/cstdint>
#elif defined(HAVE_BOOST)
#include <boost/cstdint.hpp>
#elif defined(HAVE_STDINT_H)
#include <stdint.h>
#else
typedef unsigned char uint8_t;
#endif


class Instrument;
class SMF;
class SP;

/**
 * @brief シーケンスデータを扱うためのクラス
 *
 * このクラスは次の機能を提供します:
 * - ファイルからシーケンスデータを読み込む。
 * - ファイルから読み込んだシーケンスデータを再生する。
 * - シーケンスデータの再生結果を波形データとして出力する。
 *
 * 現在再生可能なシーケンスデータの形式はSMF(標準MIDIファイル)のみです。
 *
 * @code
 * // ファイルからSMFデータを読み込み、データの終わりまで再生する例
 * Song song;
 * SMF smf(song);
 * song.load_file("sample.mid");
 * song.play();
 * while (song.is_playing()) {
 *   song.update();
 *   // 1/60秒経過するまで待つ処理をここに入れる
 * }
 * @endcode
 */
class Song
{
public:
  Song();
  ~Song();
  void update();
  bool load_file(const SP &filename);
  Instrument *instrument() const { return inst_; }
  void set_instrument(Instrument *inst);
  void play();
  bool is_playing() const;
  bool mix_audio(uint8_t *buf, const size_t len);
private:
  SMF *smf_;
  Instrument *inst_;
};

#endif // !defined(SONG_HPP_INCLUDED)
