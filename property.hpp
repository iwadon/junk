#ifndef PROPERTY_HPP_INCLUDED
#define PROPERTY_HPP_INCLUDED 1

#include <cassert>
#include <cstddef>

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

#endif // !defined(PROPERTY_HPP_INCLUDED)
