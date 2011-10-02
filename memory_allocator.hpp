#ifndef MEMORY_ALLOCATOR_HPP_INCLUDED
#define MEMORY_ALLOCATOR_HPP_INCLUDED 1

#include <cstddef>
#include <stdint.h>

class MemoryAllocator
{
private:
  static const uint32_t CHUNK_ID_USED = 0x75536544U; // 'uSeD'
  static const uint32_t CHUNK_ID_FREE = 0x46724565U; // 'FrEe'
  static const uint32_t CHUNK_ID_END_ = 0x654e64ffU; // 'eNd\xff'

  struct Chunk
  {
    uint32_t id;		// チャンクID
    uint32_t size;		// メモリの大きさ
    uint32_t prev;		// 前のチャンクへのオフセット(0:先頭のチャンク)
    uint32_t next;		// 後ろのチャンクへのオフセット(0:末尾のチャンク)
    Chunk *prev_chunk() { return reinterpret_cast<Chunk *>(reinterpret_cast<int8_t *>(this) - prev); }
    Chunk *next_chunk() { return reinterpret_cast<Chunk *>(reinterpret_cast<int8_t *>(this) + next); }
  };

public:
  static const size_t PADDING_SIZE = sizeof (Chunk);

  MemoryAllocator(void *addr, size_t size); // コンストラクタ
  ~MemoryAllocator();			    // デストラクタ
  void *allocate(const size_t size);	    // 確保
  void free(void *addr);		    // 開放
  size_t max_free_size() const;		    // 確保可能なメモリの大きさの最大値

private:
  Chunk *top_;
};

#endif // !defined(MEMORY_ALLOCATOR_HPP_INCLUDED)
