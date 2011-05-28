#ifndef AUDIO_STREAM_HPP_INCLUDED
#define AUDIO_STREAM_HPP_INCLUDED 1

#include <cstddef>

/**
 * @brief オーディオデータを読み出すためのストリーム
 *
 * @sa OscillatorStream
 */
class AudioStream
{
public:
  /**
   * @brief データを読み出す
   *
   * @param [out] buf   読みだしたデータを格納するためのバッファ。
   * @param [in]  len   データを読み出したい長さ。バイト単位で指定します。
   * @param [in]  ratio データを読み出す速度の比率。1.0を等速、2.0を倍速、0.5を1/2速として指定します。
   *
   * @note この関数の引数である読み出し速度(ratio)はオーディオデータにおける音程を想定しています。
   *       つまり、2.0指定時は1オクターブ高く、0.5指定時は1オクターブ低い音程のオーディオデータを
   *       読み出せるような実装が求められます。
   *
   * @return 読み出したデータの長さ。
   *
   * @sa OscillatorStream::read
   *
   * @code
   * // class AudioStreamSample : public AudioStream { ... };
   * // AudioStreamSample as;
   * // char buf[];
   * as.read(buf, sizeof buf, 1.0f); // 原音の音程で読みだす。
   * as.read(buf, sizeof buf, 2.0f); // 1オクターブ高い音程で読みだす。
   * as.read(buf, sizeof buf, 0.5f); // 1オクターブ低い音程で読みだす。
   * @endcode
   */
  virtual size_t read(void *buf, const size_t len, const float ratio) = 0;
};

#endif // !defined(AUDIO_STREAM_HPP_INCLUDED)
