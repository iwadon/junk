#pragma once

#include "memory_pool.hpp"
#include <list>

template <class T>
class InstancePool
{
public:
  typedef T *pointer_type;

  ~InstancePool()
  {
    for (auto ptr: pointers_) {
      ptr->~T();
      pool_.Deallocate(ptr);
    }
  }

  pointer_type Construct()
  {
    auto ptr = pool_.Allocate();
    if (ptr != NULL) {
      new (ptr) T();
      pointers_.push_back(static_cast<pointer_type>(ptr));
    }
    return static_cast<pointer_type>(ptr);
  }

  template <class A0>
  pointer_type Construct(const A0 &a0)
  {
    auto ptr = pool_.Allocate();
    if (ptr != NULL) {
      new (ptr) T(a0);
      pointers_.push_back(static_cast<pointer_type>(ptr));
    }
    return static_cast<pointer_type>(ptr);
  }

  template <class A0, class A1>
  pointer_type Construct(const A0 &a0, const A1 &a1)
  {
    auto ptr = pool_.Allocate();
    if (ptr != NULL) {
      new (ptr) T(a0, a1);
      pointers_.push_back(static_cast<pointer_type>(ptr));
    }
    return static_cast<pointer_type>(ptr);
  }

  template <class A0, class A1, class A2>
  pointer_type Construct(const A0 &a0, const A1 &a1, const A2 &a2)
  {
    auto ptr = pool_.Allocate();
    if (ptr != NULL) {
      new (ptr) T(a0, a1, a2);
      pointers_.push_back(static_cast<pointer_type>(ptr));
    }
    return static_cast<pointer_type>(ptr);
  }

  void Destroy(pointer_type ptr)
  {
    if (ptr != NULL) {
      ptr->~T();
      pointers_.remove(ptr);
      pool_.Deallocate(ptr);
      printf("count = %zu\n", pointers_.size());
    }
  }

private:
  MemoryPool<sizeof (T)> pool_;
  std::list<pointer_type> pointers_;
};
