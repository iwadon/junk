#include "memory_allocator.hpp"

/**
 * @brief コンストラクタ
 *
 * @param [in] addr 使用するメモリ領域の先頭アドレス。
 * @param [in] size 使用するメモリ領域の大きさ(バイト単位)。
 */
MemoryAllocator::MemoryAllocator(void *addr, size_t size)
  : top_(reinterpret_cast<Chunk *>(addr))
{
  top_->id = CHUNK_ID_FREE;
  top_->size = size - sizeof (Chunk);
  top_->prev = 0;
  top_->next = 0;
}

/**
 * @brief デストラクタ
 */
MemoryAllocator::~MemoryAllocator()
{
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
  size_t sz = (size + 3) / 4 * 4;
  Chunk *c = top_;
  while (true) {
    if (c->id == CHUNK_ID_FREE && c->size >= sz) {
      break;
    }
    if (c->next == 0) {
      return NULL;
    }
    c = c->next_chunk();
  }
  if (c->size > sizeof (Chunk) + sz) {
    Chunk *c2 = reinterpret_cast<Chunk *>(reinterpret_cast<int8_t *>(c) + sizeof (Chunk) + sz);
    c2->id = CHUNK_ID_FREE;
    c2->size = c->size - sizeof (Chunk) - sz;
    c2->prev = sizeof (Chunk) + sz;
    c2->next = c->next;
    c->next = c2->prev;
  }
  c->id = CHUNK_ID_USED;
  c->size = sz;
  return reinterpret_cast<int8_t *>(c) + sizeof (Chunk);
}

void MemoryAllocator::free(void *addr)
{
  Chunk *c = reinterpret_cast<Chunk *>(reinterpret_cast<int8_t *>(addr) - sizeof (Chunk));
  c->id = CHUNK_ID_FREE;
  if (c->next != 0) {
    Chunk *nc = c->next_chunk();
    if (nc->id == CHUNK_ID_FREE) {
      c->size += sizeof (Chunk) + nc->size;
      c->next = nc->next;
    }
  }
  if (c->prev != 0) {
    Chunk *pc = c->prev_chunk();
    if (pc->id == CHUNK_ID_FREE) {
      pc->size += sizeof (Chunk) + c->size;
      pc->next = c->next;
    }
  }
}

size_t MemoryAllocator::max_free_size() const
{
  size_t max_size = 0;
  Chunk *c = top_;
  while (true) {
    if (c->id == CHUNK_ID_FREE && c->size > max_size) {
      max_size = c->size;
    }
    if (c->next == 0) {
      break;
    }
    c = c->next_chunk();
  }
  return max_size;
}
