#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "function.hpp"
#include <gtest/gtest.h>
#include <functional>
#include <boost/function.hpp>

static int func1()
{
  return 123;
}

static int n2 = 0;

static void func2()
{
  ++n2;
}

static int func3(const int n)
{
  return n + 1;
}

static int func3b(int n)
{
  return n + 2;
}

static int func4(int &n)
{
  return ++n;
}

static int func5(const int &n)
{
  return n + 1;
}

static float func6(int a1, float a2)
{
  return a1 + a2;
}

static float func7(int a1, float a2, int a3)
{
  return (a1 + a2) * a3;
}

struct A
{
  int a_;

  A(int a)
    : a_(a)
  {
  }

  int func8(int b)
  {
    return a_ + b;
  }

  static int func9(A &obj, int b)
  {
    return obj.func8(b);
  }
};

TEST(FunctionTest, value)
{
  // int()
  Function<int()> f1(func1);
  EXPECT_EQ(123, f1());

  // void()
  Function<void()> f2(func2);
  f2();
  EXPECT_EQ(1, n2);

  // int(int) or int(const int)
  Function<int(int)> f3(func3);
  EXPECT_EQ(2, f3(1));
  Function<int(const int)> f3b(func3b);
  EXPECT_EQ(3, f3b(1));

  // int(int &)
  Function<int(int&)> f4(func4);
  int n = 1;
  EXPECT_EQ(2, f4(n));
  EXPECT_EQ(2, n);

  // int(const int &)
  Function<int(const int &)> f5(func5);
  EXPECT_EQ(2, f5(1));

  // float(int, float)
  Function<float(int, float)> f6(func6);
  EXPECT_EQ(3.5f, f6(1, 2.5f));

  Function<float(int, float, int)> f7(func7);
  EXPECT_EQ(10.5f, f7(1, 2.5f, 3));

  A a(3);
  //Function<int(int)> f8 = std::bind1st(std::mem_fun(&A::func8), &a);
  boost::function<int(int)> f8 = std::bind1st(std::mem_fun(&A::func8), &a);
  EXPECT_EQ(5, f8(2));
  Function<int(A &, int)> f9(&A::func9);
  EXPECT_EQ(5, f9(a, 2));
}
