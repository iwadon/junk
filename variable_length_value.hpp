#ifndef VARIABLE_LENGTH_VALUE_HPP_INCLUDED
#define VARIABLE_LENGTH_VALUE_HPP_INCLUDED 1

#include <cassert>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif

class VariableLengthValue
{
public:
  typedef uint32_t value_type;
  typedef char data_type;
  typedef size_t len_type;
  VariableLengthValue(const data_type *data, const len_type len) { set_data(data, len); }
  VariableLengthValue(const value_type value) { set_value(value); }
  void data(const data_type **data, len_type *len) const;
  len_type set_data(const data_type *data, const len_type len);
  value_type value() const { return value_; }
  void set_value(const value_type value);
private:
  data_type data_[4];
  len_type len_;
  value_type value_;
  void convert_to_value();
  void convert_to_data();
};

#endif // !defined(VARIABLE_LENGTH_VALUE_HPP_INCLUDED)
