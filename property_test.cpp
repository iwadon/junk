#include "gtest/gtest.h"
#include <cassert>

template <typename T, typename V>
class Property
{
public:
  typedef T object_type;
  typedef V value_type;
  typedef value_type (object_type::*getter_type)() const;
  typedef void (object_type::*setter_type)(const value_type &value);

  Property(object_type *obj, getter_type getter, setter_type setter)
    : obj_(obj)
    , getter_(getter)
    , setter_(setter)
  {
    assert(obj_ != NULL);
  }

  value_type get() const
  {
    assert(obj_ != NULL);
    assert(getter_ != NULL);
    return (obj_->*getter_)();
  }

  Property &set(const value_type &value)
  {
    assert(obj_ != NULL);
    assert(setter_ != NULL);
    (obj_->*setter_)(value);
    return *this;
  }

  operator value_type() const
  {
    return get();
  }

  Property &operator=(const value_type &value)
  {
    return set(value);
  }
private:
  object_type *obj_;
  getter_type getter_;
  setter_type setter_;
};

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
