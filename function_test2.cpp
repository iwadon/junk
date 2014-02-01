// 関数または関数的なものを保持して後から呼び出すような機能をどのように実装するかを確認するためのテスト。

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <gtest/gtest.h>
#include <functional>

// Actionクラスを直接使うのが面倒なので…
class ActionBase
{
public:
  virtual ~ActionBase() {}
  virtual int invoke(int a, int b) = 0;
};

// 関数または関数的なものを保持したり後から呼び出したりするためのクラス。
template <typename F>
class Action : public ActionBase
{
public:
  Action(F action);
  virtual int invoke(int a, int b);
private:
  F action_;
};

// コンストラクタ。保持している。
template <typename F>
Action<F>::Action(F action)
  : action_(action)
{
}

// 保持したものを呼び出す。

template <typename F>
int Action<F>::invoke(int a, int b)
{
  return action_(a, b);
}

// Actionオブジェクトを生成する。Actionクラスを直接記述するのが面倒なのでこの関数に任せている。
template <typename F>
ActionBase *new_action(F action)
{
  return new Action<F>(action);
}

// ローカル関数の例。
static int add(int a, int b)
{
  return a + b;
}

// 関数オブジェクトの例。
struct FuncObj
{
  int operator()(int a, int b) const
  {
    return a + b;
  }
};

// staticなメンバー関数の例。
struct StaticMemFunc
{
  static int add_static(int a, int b)
  {
    return a + b;
  }
};

// staticではないメンバー関数の例。
struct MemFunc
{
  int add(int a, int b)
  {
    return a + b;
  }
};

// ローカル関数を使った実装例。
TEST(FunctionTest2, LocalFunc)
{
  ActionBase *a = new_action(&add);
  EXPECT_EQ(5, a->invoke(2, 3));
}

// 関数オブジェクトを使った実装例。
TEST(FunctionTest2, FuncObj)
{
  FuncObj ta;
  ActionBase *a = new_action(ta);
  EXPECT_EQ(5, a->invoke(2, 3));
}

// staticなメンバー関数を使った実装例。
TEST(FunctionTest2, StaticMemFunc)
{
  ActionBase *a = new_action(std::bind(StaticMemFunc::add_static, std::placeholders::_1, std::placeholders::_2));
  EXPECT_EQ(5, a->invoke(2, 3));
}

// staticではないメンバー関数を使った実装例。
TEST(FunctionTest2, MemFunc)
{
  MemFunc ta;
  ActionBase *a = new_action(std::bind(&MemFunc::add, &ta, std::placeholders::_1, std::placeholders::_2));
  EXPECT_EQ(5, a->invoke(2, 3));
}

// lambdaでの実装例。
TEST(FunctionTest2, BoostLambda)
{
  auto a = new_action([](int x, int y){ return x + y; });
  EXPECT_EQ(5, a->invoke(2, 3));
}

#if defined(__APPLE__) && defined(__BLOCKS__)

// ブロックでの実装例。
TEST(FunctionTest2, BlockObject)
{
  ActionBase *a = new_action(^(int a, int b) {return a + b;});
  EXPECT_EQ(5, a->invoke(2, 3));
}

#endif // defined(__APPLE__) && defined(__BLOCKS__)

// TODO: C++0xのラムダ関数での例を追加する。
