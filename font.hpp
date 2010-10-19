/**
 * @file  font.hpp
 * @brief Fontクラスの定義
 */

#ifndef FONT_HPP_INCLUDED
#define FONT_HPP_INCLUDED 1

#include "sp.hpp"

struct Texture;

/**
 * @class Font
 * @brief 画像に描かれたフォントを使って文字を描画する
 */
class Font
{
public:
  ~Font();
  bool load_file(const SP &filename);
  void draw_chr(const int x, const int y, const int chr);
  void draw_str(const int x, const int y, const SP &str);
  void draw_strf(const int x, const int y, const char *format, ...);
private:
  Texture *tex_;
};

#endif // !defined(FONT_HPP_INCLUDED)
