// StringPiece class.
// This code is based on Google Chrome's StringPiece class.

#ifndef SP_HPP_INCLUDED
#define SP_HPP_INCLUDED 1

#ifdef STDCXX_98_HEADERS
#include <cstddef>
#include <cstring>
#include <string>
#endif

class SP
{
public:
  SP() : ptr_(NULL), len_(0) {}
  SP(const char *str) : ptr_(str), len_(str == NULL ? 0 : strlen(str)) {}
  SP(const std::string &str) : ptr_(str.data()), len_(str.size()) {}
  SP(const char *offset, const size_t size) : ptr_(offset), len_(size) {}
  const char *data() const { return ptr_; }
  size_t size() const { return len_; }
  const char *c_str() const { return ptr_; }
  bool empty() const { return len_ == 0; }
  bool operator==(const SP &x) const { return (len_ == x.len_) || (memcmp(ptr_, x.ptr_, len_) == 0); }
  void CopyToString(std::string *target) const { target->assign(empty() ? "" : ptr_, len_); }
private:
  const char *ptr_;
  size_t len_;
};

#endif // !defined(SP_HPP_INCLUDED)
