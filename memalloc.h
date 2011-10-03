#ifndef MEMALLOC_H_INCLUDED
#define MEMALLOC_H_INCLUDED 1

#include <stddef.h>
#include <stdint.h>

#define MEMALLOC_CHUNK_ID_USED 0x75536544U
#define MEMALLOC_CHUNK_ID_FREE 0x46724565U

typedef struct MemAlloc MemAlloc;
typedef struct MemAllocChunk MemAllocChunk;

struct MemAlloc
{
  MemAllocChunk *top;
};

struct MemAllocChunk
{
  uint32_t id;
  uint32_t size;
  uint32_t prev;
  uint32_t next;
};

#ifdef __cplusplus
extern "C" {
#endif

void MemAllocInitialize(MemAlloc *ma, void *addr, size_t size);
void *MemAllocAllocate(MemAlloc *ma, size_t size);
void MemAllocFree(MemAlloc *ma, void *addr);
size_t MemAllocGetMaxFreeSize(MemAlloc *ma);

#ifdef __cplusplus
}
#endif

#endif // !defined(MEMALLOC_H_INCLUDED)
