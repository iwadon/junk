#ifndef PAD_HPP_INCLUDED
#define PAD_HPP_INCLUDED 1

#include <string>		// std::string
#include <boost/cstdint.hpp>	// uint32_t
#include "callback.hpp"

/// 種別
enum PAD_TYPE {
  PAD_TYPE_DUMMY,		///< 何もしない
  PAD_TYPE_HUMAN,		///< 人間が操作する
  PAD_TYPE_AUTO,		///< 自動的に操作する
  PAD_TYPE_REPLAY,		///< データで操作する
  NUM_PAD_TYPES
};

/// 状態
typedef uint32_t PAD_STATUS;
static const PAD_STATUS PAD_STATUS_LOGGING_ENABLED = 1 << 0;

/// ボタン
typedef uint32_t PAD_BUTTON;
static const PAD_BUTTON PAD_BUTTON_U = 1 << 0;
static const PAD_BUTTON PAD_BUTTON_D = 1 << 1;
static const PAD_BUTTON PAD_BUTTON_L = 1 << 2;
static const PAD_BUTTON PAD_BUTTON_R = 1 << 3;
static const PAD_BUTTON PAD_BUTTON_A = 1 << 4;
static const PAD_BUTTON PAD_BUTTON_B = 1 << 5;
static const PAD_BUTTON PAD_BUTTON_X = 1 << 6;
static const PAD_BUTTON PAD_BUTTON_Y = 1 << 7;
static const PAD_BUTTON PAD_BUTTON_START = 1 << 16;
static const PAD_BUTTON PAD_BUTTON_FAST = 1 << 30;
static const PAD_BUTTON PAD_BUTTON_SLOW = 1 << 31;

/// アナログ入力
struct PadAnalog {
  float x;
  float y;
  bool operator==(const PadAnalog &other) const { return x == other.x && y == other.y; }
};

/// データ
struct PadData
{
  static const PadData ZERO;	///< 空データ

  PadAnalog al;			///< アナログスティック(左)
  PadAnalog ar;			///< アナログスティック(右)
  PAD_BUTTON button;		///< ボタン

  /**
   * @brief データを設定する
   *
   * @param [in] data 設定するデータ。
   */
  void set(const PadData &data)
  {
    al = data.al;
    ar = data.ar;
    button = data.button;
  }

  /**
   * @brief データを初期状態に戻す
   */
  void reset()
  {
    set(ZERO);
  }

  std::string to_string() const;
};

/// パッドの基本クラス
struct PadBase : public PadData
{
  PAD_TYPE type;
  PAD_BUTTON prev_button;
  PAD_BUTTON button_on;
  PAD_BUTTON button_off;
  PAD_STATUS status;
  PadData *log_top;
  PadData *log_bot;
  PadData *log_cur;

  PadBase(const PAD_TYPE t)
    : type(t)
    , prev_button(0)
    , status(0)
    , log_top(NULL)
    , log_bot(NULL)
    , log_cur(NULL)
  {
    reset();
  }

  /// 更新
  void update()
  {
    on_pre_update();
    on_update();
    on_post_update();
  }

  // 更新処理。派生クラスで定義する。
  virtual void on_update() = 0;

  // 更新の前処理
  void on_pre_update()
  {
    prev_button = button;
    button = 0;
  }

  // 更新の後処理
  void on_post_update()
  {
    button_on = button & ~prev_button;
    button_off = prev_button & ~button;

    if (status & PAD_STATUS_LOGGING_ENABLED && log_cur < log_bot) {
      log_cur->al = al;
      log_cur->ar = ar;
      log_cur->button = button;
      ++log_cur;
    }
  }

  void set_log_buffer(void *buf, size_t num)
  {
    log_top = log_cur = static_cast<PadData *>(buf);
    log_bot = log_top + num;
  }

  void enable_logging()
  {
    status |= PAD_STATUS_LOGGING_ENABLED;
  }

  void disable_logging()
  {
    status &= ~PAD_STATUS_LOGGING_ENABLED;
  }
};

/// ダミーパッド
struct DummyPad : public PadBase
{
  DummyPad() : PadBase(PAD_TYPE_DUMMY) {}
  void on_update() {}
};

/**
 * @brief 人間が操作するパッド
 *
 * キーボードからの入力を元にパッドデータを作る。
 */
struct HumanPad : public PadBase
{
  HumanPad()
    : PadBase(PAD_TYPE_HUMAN)
  {
  }

  void on_update();
};

/**
 * @brief 自動的に操作するパッド
 *
 * 実際の操作はコールバック関数内で行う。
 */ 
struct AutoPad : public PadBase
{
  // コールバック
  typedef void (*update_callback_type)(AutoPad *pad, void *arg);
  Callback<update_callback_type, 1> update_cb;

  AutoPad()
    : PadBase(PAD_TYPE_AUTO)
  {
  }

  /**
   * @brief 更新
   *
   * パッドデータを作るため、コールバック関数を呼び出す。
   */
  void on_update()
  {
    update_cb.call(this);
  }
};

/// リプレイデータ
struct ReplayData
{
  const PadData *top;
  const PadData *bot;
  const PadData *cur;
  ReplayData() : top(NULL), bot(NULL), cur(NULL) {}
};

/// リプレイを再生するパッド
struct ReplayPad : public PadBase
{
  ReplayData replay_data;

  ReplayPad()
    : PadBase(PAD_TYPE_REPLAY)
  {
  }

  /**
   * @brief 更新
   *
   * リプレイデータを読み出し、パッドデータを更新する。
   */
  void on_update()
  {
    if (replay_data.cur < replay_data.bot) {
      set(*replay_data.cur);
      ++replay_data.cur;
    } else {
      reset();
    }
  }

  /**
   * @brief リプレイデータを設定する
   *
   * リプレイデータの読み出し位置が先頭に戻る。
   *
   * @param [in] data リプレイデータ。
   * @param [in] num  リプレイデータに含まれるパッドデータの個数。
   */
  void set_replay_data(const void *data, size_t num)
  {
    replay_data.top = replay_data.cur = reinterpret_cast<const PadData *>(data);
    replay_data.bot = replay_data.top + num;
  }
};

#endif // !defined(PAD_HPP_INCLUDED)
