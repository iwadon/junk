#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "function.hpp"

class FunctionTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(FunctionTest);
  CPPUNIT_TEST(test_value);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_value();
};

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

void FunctionTest::test_value()
{
  // int()
  Function<int()> f1(func1);
  CPPUNIT_ASSERT_EQUAL(123, f1());

  // void()
  Function<void()> f2(func2);
  f2();
  CPPUNIT_ASSERT_EQUAL(1, n2);

  // int(int) or int(const int)
  Function<int(int)> f3(func3);
  CPPUNIT_ASSERT_EQUAL(2, f3(1));
  Function<int(const int)> f3b(func3b);
  CPPUNIT_ASSERT_EQUAL(3, f3b(1));

  // int(int &)
  Function<int(int&)> f4(func4);
  int n = 1;
  CPPUNIT_ASSERT_EQUAL(2, f4(n));
  CPPUNIT_ASSERT_EQUAL(2, n);

  // int(const int &)
  Function<int(const int &)> f5(func5);
  CPPUNIT_ASSERT_EQUAL(2, f5(1));

  // float(int, float)
  Function<float(int, float)> f6(func6);
  CPPUNIT_ASSERT_EQUAL(3.5f, f6(1, 2.5f));

  Function<float(int, float, int)> f7(func7);
  CPPUNIT_ASSERT_EQUAL(10.5f, f7(1, 2.5f, 3));
}

CPPUNIT_TEST_SUITE_REGISTRATION(FunctionTest);
