#include "spec.hpp"

template <class T>
class A
{
public:
  A()
    : value_()
  {
  }
  void set_value(const T &value)
  {
    value_ = value;
  }
  bool operator==(const A<T> &other) const
  {
    return value_ == other.value_;
  }
private:
  T value_;
  A(const A& other);
  A& operator =(const A& other);
};

int main()
{
  A<int> a1;
  A<int> a2;
  A<float> a3;
  A<int> a4;
  a4.set_value(123);
  _(a1) SHOULD(== a2);
  _(a1) SHOULD(== a3);
  _(a1) SHOULD(== a4);
  return 0;
}
