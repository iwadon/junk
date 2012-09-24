#ifndef WAV_HPP_INCLUDED
#define WAV_HPP_INCLUDED 1

#include <SDL.h>
#include "sp.hpp"

/// @brief WAV形式のデータを扱うためのクラス
struct Wav
{
  void *data;			///< 波形データの先頭アドレス
  size_t len;			///< 波形データの長さ(バイト単位)
  size_t pos;			///< 次の再生開始位置(サンプル単位)

  Wav();
  ~Wav();

  bool LoadFile(const SP &filename);

  bool ParseData(const void *data, size_t size);
  bool ParseData(SDL_RWops *f);

  /// @brief 指定された長さのサンプルを読み出します
  ///
  /// @param [out] buf     読みだしたサンプルを格納するバッファです。
  /// @param [in]  samples 読みだすサンプルの長さです。サンプル単位で指定します。
  ///
  /// @return 実際に読み出せたサンプルの長さを返します。
  size_t ReadSamples(void *buf, size_t samples);
};

#endif // !defined(WAV_HPP_INCLUDED)
