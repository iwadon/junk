#ifndef SDL_ALLOCATOR_HPP_INCLUDED
#define SDL_ALLOCATOR_HPP_INCLUDED 1

#include <SDL.h>
#include <cstddef>

template <typename T>
class SDLAllocator;

template <>
class SDLAllocator<void>
{
public:
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef void *pointer;
  typedef const void *const_pointer;
  typedef void value_type;

  template <typename T1>
  struct rebind
  {
    typedef SDLAllocator<T1> other;
  };
};

template <typename T>
class SDLAllocator
{
public:
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T value_type;

  template <typename T1>
  struct rebind
  {
    typedef SDLAllocator<T1> other;
  };

  SDLAllocator() throw() {}

  SDLAllocator(const SDLAllocator &) throw() {}

  template <typename T1>
  SDLAllocator(const SDLAllocator<T1> &) throw() {}

  ~SDLAllocator() throw() {}

  pointer address(reference x) const
  {
    return &x;
  }

  const_pointer address(const_reference x) const
  {
    return &x;
  }

  pointer allocate(size_type n, SDLAllocator<void>::const_pointer /*hint*/ = 0)
  {
    return static_cast<T *>(SDL_malloc(n * sizeof (T)));
  }

  void deallocate(pointer p, size_type)
  {
    SDL_free(p);
  }

  size_type max_size() const
  {
    return size_type(-1) / sizeof (T);
  }

  void construct(pointer p, const T &value)
  {
    new(p) T(value);
  }

  void destroy(pointer p)
  {
    p->~T();
  }
};

template <typename T1, typename T2>
bool operator==(const SDLAllocator<T1> &, const SDLAllocator<T2> &) throw()
{
  return true;
}

template <typename T1, typename T2>
bool operator!=(const SDLAllocator<T1> &, const SDLAllocator<T2> &) throw()
{
  return false;
}

#endif // !defined(SDL_ALLOCATOR_HPP_INCLUDED)
