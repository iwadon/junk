#ifndef SDL_CONSOLE_APP_HPP_INCLUDED
#define SDL_CONSOLE_APP_HPP_INCLUDED 1

#include "frame_wait_timer.hpp"

/// SDLを使ったコンソールアプリのベースとなるクラスです。
///
/// ウィンドウは使わないがメインループは必要なアプリを簡単に実装するのが目的です。
///
/// このクラスを継承して、初期化、終了、更新処理を実装します。
class SDLConsoleApp
{
public:
  /// コンストラクタです。
  SDLConsoleApp();

  /// デストラクタです。
  virtual ~SDLConsoleApp();

  /// @brief アプリを実行します。
  ///
  /// main()から呼び出されることを想定しています。
  ///
  /// @param[in] argc 引数の数。main()に渡されるargcをそのまま渡すことを想定しています。
  /// @param[in] argv 引数の配列。main()に渡されるargvをそのまま渡すことを想定しています。
  ///
  /// @retval 0 正常に終了しました。
  /// @retval 1 エラーが起きました。
  virtual int Run(int argc, char *argv[]);

protected:
  /// @brief 初期化時に呼び出される関数です。
  ///
  /// @param[in] argc 引数の数。main()に渡されるargcをそのまま渡すことを想定しています。
  /// @param[in] argv 引数の配列。main()に渡されるargvをそのまま渡すことを想定しています。
  ///
  /// @retval true  正常に初期化できました。
  /// @retval false 初期化中にエラーが起きました。
  virtual bool OnInitialize(int argc, char *argv[]) = 0;

  /// 終了時に呼び出される関数です。
  virtual void OnFinalize() = 0;

  /// 更新時に呼び出される関数です。
  virtual void OnUpdate() = 0;

  /// メインループを終了します。
  ///
  /// この関数を呼び出したループが終了するとメインループを抜けて、終了処理へ移行します。
  void QuitMainLoop();

private:
  FrameWaitTimer fwt_;
};

#endif // !defined(SDL_CONSOLE_APP_HPP_INCLUDED)
