#include "property.hpp"
#include "gtest/gtest.h"

class Foo
{
public:
  Property<Foo, int> prop;

  Foo()
    : prop(this, &Foo::get_value, &Foo::set_value)
    , value_(0xdeadbeef)
  {
  }
protected:
  int get_value() const
  {
    return value_;
  }

  void set_value(const int &value)
  {
    value_ = value;
  }
private:
  int value_;
};

TEST(PropertyTest, get) {
  Foo a;
  Foo b;
  EXPECT_EQ(0xdeadbeef, a.prop);
  EXPECT_EQ(0xdeadbeef, b.prop);
  EXPECT_EQ(a.prop, b.prop);
}

TEST(PropertyTest, set) {
  Foo a;
  Foo b;
  a.prop = 123;
  b.prop = 123;
  EXPECT_EQ(123, a.prop);
  EXPECT_EQ(123, b.prop);
  EXPECT_EQ(a.prop, b.prop);
  b.prop = 456;
  EXPECT_EQ(456, b.prop);
  EXPECT_NE(a.prop, b.prop);
}
