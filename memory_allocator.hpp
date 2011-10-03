#ifndef MEMORY_ALLOCATOR_HPP_INCLUDED
#define MEMORY_ALLOCATOR_HPP_INCLUDED 1

#include <cstddef>

class MemoryAllocator
{
public:
  MemoryAllocator(void *addr, size_t size); // コンストラクタ
  ~MemoryAllocator();			    // デストラクタ
  void *allocate(const size_t size);	    // 確保
  void free(void *addr);		    // 開放
  size_t max_free_size() const;		    // 確保可能なメモリの大きさの最大値

private:
  void *ma_;
};

#endif // !defined(MEMORY_ALLOCATOR_HPP_INCLUDED)
