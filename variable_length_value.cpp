#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cstring>
#include "variable_length_value.hpp"

void VariableLengthValue::data(const data_type **data, len_type *len) const
{
  if (data != NULL) {
    *data = data_ + (4 - len_);
  }
  if (len != NULL) {
    *len = len_;
  }
}

VariableLengthValue::len_type VariableLengthValue::set_data(const data_type *data, const len_type len)
{
  assert(data != NULL);
  len_type l = len;
  if (l == 0) {
    l = 1;
    const data_type *d = data;
    while (*d & 0x80) {
      ++d;
      ++l;
    }
  }
  len_ = l;
  memcpy(data_, data, len_);
  convert_to_value();
  return len_;
}

void VariableLengthValue::set_value(const value_type value)
{
  value_ = value;
  convert_to_data();
}

void VariableLengthValue::convert_to_data()
{
  value_type v = value_;
  data_type *d = &data_[3];
  *d = v & 0x7f;
  len_ = 1;
  while ((v >>= 7) != 0) {
    *--d = 0x80 | (v & 0x7f);
    ++len_;
  }
}

void VariableLengthValue::convert_to_value()
{
  value_type v = 0;
  data_type *d = data_;
  for (len_type l = 0; l < len_; ++d, ++l) {
    v <<= 7;
    v |= *d & 0x7f;
  }
  value_ = v;
}
