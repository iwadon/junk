#pragma once

#include <list>
#include <cstdlib>

template <size_t SZ>
class MemoryPool
{
public:
  ~MemoryPool()
  {
    printf("%s\n", __PRETTY_FUNCTION__);
    for (auto ptr: pointers_) {
      free(ptr);
    }
  }

  void *Allocate()
  {
    void *ptr = malloc(SZ);
    pointers_.push_back(ptr);
    return ptr;
  }

  void Deallocate(void *ptr)
  {
    if (ptr != NULL) {
      pointers_.remove(ptr);
      free(ptr);
    }
  }

private:
  typedef std::list<void *> pointer_list_type;
  pointer_list_type pointers_;
};
