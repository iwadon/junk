/**
 * @file  font.cpp
 * @brief Fontクラスの実装
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "font.hpp"
#include <cassert>
#include <cstdarg>
#include <SDL.h>
#include "sdl_logger.hpp"
#include "texture.hpp"
#include "texture_pool.hpp"

/// コンストラクタ
Font::Font(SDL_Renderer *renderer)
  : renderer_(renderer)
  , tex_(NULL)
{
  assert(renderer_ != NULL);
}

/// デストラクタ
Font::~Font()
{
  if (tex_ != NULL) {
    TexturePool::get_instance().destroy(tex_);
  }
}

/**
 * @brief ファイルを読み込む
 * @param [in] filename ファイル名。
 * @retval true  正常にファイルを読み込めた。
 * @retval false ファイルを読み込んでいる最中にエラーが起きた。
 */
bool Font::load_file(const SP &filename)
{
  assert(filename.data() != NULL);
  assert(renderer_ != NULL);
  if (tex_ != NULL) {
    TexturePool::get_instance().destroy(tex_);
  }
  tex_ = TexturePool::get_instance().load_file(renderer_, filename);
  return tex_ != NULL;
}

/**
 * @brief 文字を描画する
 * @param [in] x   X座標。
 * @param [in] y   Y座標。
 * @param [in] chr 文字。
 */
void Font::draw_chr(const int x, const int y, const int chr)
{
  assert(tex_ != NULL);
  assert(renderer_ != NULL);
  SDL_Rect srcrect;
  unsigned char c = chr;
  srcrect.x = 8 * (c & 0xf);
  srcrect.y = 8 * ((c & 0xf0) >> 4);
  srcrect.w = 8;
  srcrect.h = 8;
  SDL_Rect dstrect;
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = 8;
  dstrect.h = 8;
  int result;
  result = SDL_RenderCopy(renderer_, tex_->texture, &srcrect, &dstrect);
  if (result != 0) {
    SDL_ERROR(SDL_RenderCopy);
  }
}

/**
 * @brief 文字列を描画する
 * @param [in] x   X座標。
 * @param [in] y   Y座標。
 * @param [in] str 文字列。
 */
void Font::draw_str(const int x, const int y, const SP &str)
{
  assert(str.data() != NULL);
  int x_ = x;
  int y_ = y;
  for (const char *p = str.data(); *p != '\0'; ++p) {
    switch (*p) {
    case '\n':
      x_ = x;
      y_ += 8;
      break;
    default:
      draw_chr(x_, y_, *p);
      x_ += 8;
      break;
    }
  }
}

/**
 * @brief 指定された書式に変換された文字列を描画する
 * @param [in] x      X座標。
 * @param [in] y      Y座標。
 * @param [in] format 書式文字列。printf(3)などで使われている書式を使う。
 */
void Font::draw_strf(const int x, const int y, const char *format, ...)
{
  assert(format != NULL);
  va_list args;
  va_start(args, format);
  draw_strfv(x, y, format, args);
  va_end(args);
}

void Font::draw_strfv(const int x, const int y, const char *format, va_list args)
{
  assert(format != NULL);
  char buf[256];
  vsnprintf(buf, sizeof buf, format, args);
  draw_str(x, y, buf);
}
