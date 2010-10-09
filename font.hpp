/**
 * @file  font.hpp
 * @brief Fontクラスの定義
 */

#ifndef FONT_HPP_INCLUDED
#define FONT_HPP_INCLUDED 1

struct Texture;

/**
 * @class Font
 * @brief 画像に描かれたフォントを使って文字を描画する
 */
class Font
{
public:
  ~Font();
  bool load_file(const char *filename);
  void draw_chr(const int x, const int y, const int chr);
  void draw_str(const int x, const int y, const char *str);
  void draw_strf(const int x, const int y, const char *format, ...);
private:
  Texture *tex_;
};

#endif // !defined(FONT_HPP_INCLUDED)
