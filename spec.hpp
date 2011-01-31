#ifndef SPEC_HPP_INCLUDED
#define SPEC_HPP_INCLUDED 1

#include <iostream>

template <class T>
struct Spec
{
  const T &expected;
  const std::string str;
  const std::string file;
  const int line;
  std::string actual_str;
  Spec(const T &expected_, const char *str_, const char *file_, const int line_)
    : expected(expected_)
    , str(str_)
    , file(file_)
    , line(line_)
  {
  }
  Spec &should(const char *actual_str_)
  {
    actual_str = actual_str_;
    return *this;
  }
#define DEFOP(x)							\
  void operator x(const T &actual) const {				\
    if (expected x actual) {						\
    } else {								\
      std::cerr << file << ": " << line << ": failed: " << str << " " << actual_str << std::endl; \
    }									\
  }									\
  template <class O> void operator x(const O &/*actual*/) const {	\
    std::cerr << file << ": " << line << ": type mismatched: " << str << " " << actual_str << std::endl; \
  }
  DEFOP(==);
#undef DEFOP
};

template <class T>
inline Spec<T> make_spec(const T &expected, const char *str, const char *file, const int line)
{
  Spec<T> a(expected, str, file, line);
  return a;
}

#define _(x) make_spec((x), #x, __FILE__, __LINE__)
#define SHOULD(x) .should(#x) x

#endif // !defined(SPEC_HPP_INCLUDED)
