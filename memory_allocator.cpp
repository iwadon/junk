#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "memory_allocator.hpp"
#include "memalloc.h"

#define MA reinterpret_cast<MemAlloc *>(ma_)

/**
 * @brief コンストラクタ
 *
 * @param [in] addr 使用するメモリ領域の先頭アドレス。
 * @param [in] size 使用するメモリ領域の大きさ(バイト単位)。
 */
MemoryAllocator::MemoryAllocator(void *addr, size_t size)
  : ma_(reinterpret_cast<void *>(new MemAlloc))
{
  MemAllocInitialize(MA, addr, size);
}

/**
 * @brief デストラクタ
 */
MemoryAllocator::~MemoryAllocator()
{
  delete reinterpret_cast<MemAlloc *>(MA);
}

/**
 * @brief メモリを確保する
 *
 * @param [in] 確保したいメモリの大きさ(バイト単位)。
 *
 * @retval NULL以外 確保したメモリへのポインタ。
 * @retval NULL     メモリを確保出来なかった。
 */
void *MemoryAllocator::allocate(const size_t size)
{
  return MemAllocAllocate(MA, size);
}

void MemoryAllocator::free(void *addr)
{
  MemAllocFree(MA, addr);
}

size_t MemoryAllocator::max_free_size() const
{
  return MemAllocGetMaxFreeSize(MA);
}
