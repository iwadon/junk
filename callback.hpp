#ifndef CALLBACK_HPP_INCLUDED
#define CALLBACK_HPP_INCLUDED 1

#include <cstring>

/**
 * @brief コールバックID
 *
 * コールバック毎に与えられるIDで、特定のコールバックを示すために使う。
 * 値は必ず0以外とする。0は無効なIDとする。
 */
typedef uint32_t CALLBACK_ID;

/**
 * @brief コールバック
 *
 * @tparam F コールバック関数の型。引数の末尾には必ずvoid *があるものとする。
 * @tparam N 登録可能なコールバックの数。
 */
template <class F, size_t N>
class Callback
{
public:
  // コンストラクタ
  Callback()
    : id_(0)
  {
    memset(items_, 0, sizeof items_);
  }

  // 登録
  CALLBACK_ID set(F func, void *arg)
  {
    Item *item = get_free_item();
    if (item == NULL) {
      return 0;
    }
    item->id = get_next_id();
    item->entry = func;
    item->arg = arg;
    return item->id;
  }

  // 解除
  void unset(const CALLBACK_ID id)
  {
    Item *item = find_item(id);
    if (item != NULL) {
      item->id = 0;
      item->entry = NULL;
      item->arg = NULL;
    }
  }

  /**
   * @brief 登録済みのコールバックを全て呼び出す
   */
  void call() const
  {
    for (size_t i = 0; i < N; ++i) {
      Item const *item = &items_[i];
      if (item->id != 0) {
	item->entry(item->arg);
      }
    }
  }
  void call()
  {
    for (size_t i = 0; i < N; ++i) {
      Item *item = &items_[i];
      if (item->id != 0) {
	item->entry(item->arg);
      }
    }
  }

  /**
   * @brief 登録済みのコールバックを全て呼び出す
   *
   * @param a0 一つ目の引数。
   */
  template <class A0>
  void call(A0 a0) const
  {
    for (size_t i = 0; i < N; ++i) {
      Item const *item = &items_[i];
      if (item->id != 0) {
	item->entry(a0, item->arg);
      }
    }
  }
  template <class A0>
  void call(A0 a0)
  {
    for (size_t i = 0; i < N; ++i) {
      Item *item = &items_[i];
      if (item->id != 0) {
	item->entry(a0, item->arg);
      }
    }
  }

private:
  struct Item
  {
    CALLBACK_ID id;
    F entry;
    void *arg;
  };

  Item items_[N];
  CALLBACK_ID id_;

  Item *find_item(const CALLBACK_ID id)
  {
    for (size_t i = 0; i < N; ++i) {
      Item *item = &items_[i];
      if (item->id == id) {
	return item;
      }
    }
    return NULL;
  }

  Item *get_free_item()
  {
    for (size_t i = 0; i < N; ++i) {
      Item *item = &items_[i];
      if (item->id == 0) {
	return item;
      }
    }
    return NULL;
  }

  CALLBACK_ID get_next_id()
  {
    ++id_;
    if (id_ == 0) {
      ++id_;
    }
    return id_;
  }
};

#endif // !defined(CALLBACK_HPP_INCLUDED)
