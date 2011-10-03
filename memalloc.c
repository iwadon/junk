#include "memalloc.h"
#include <assert.h>
#include <stdio.h>

#define ALIGN_SIZE 4

static MemAllocChunk *prev_chunk(MemAllocChunk *c)
{
  return (MemAllocChunk *)(((int8_t *) c) - c->prev);
}

static MemAllocChunk *next_chunk(MemAllocChunk *c)
{
  return (MemAllocChunk *)(((int8_t *) c) + c->next);
}

static void print_map(MemAlloc *ma)
{
  MemAllocChunk *c = ma->top;
  printf("Address          ID   Size       Prev       Next\n");
  printf("================ ==== ========== ========== ==========\n");
  while (!0) {
    printf("%16p %s %10u %10u %10u\n", c, c->id == MEMALLOC_CHUNK_ID_FREE ? "FREE" : "USED", c->size, c->prev, c->next);
    if (c->next == 0) {
      break;
    }
    c = next_chunk(c);
  }
  printf("[END]\n");
}

void MemAllocInitialize(MemAlloc *ma, void *addr, size_t size)
{
  assert(ma != NULL);
  assert(addr != NULL);
  assert(size > sizeof (MemAllocChunk));
  ma->top = addr;
  ma->top->id = MEMALLOC_CHUNK_ID_FREE;
  ma->top->size = size - sizeof (MemAllocChunk);
  ma->top->prev = ma->top->next = 0;
  //print_map(ma);
}

void *MemAllocAllocate(MemAlloc *ma, size_t size)
{
  size_t sz = (size + (ALIGN_SIZE - 1)) / ALIGN_SIZE * ALIGN_SIZE;
  MemAllocChunk *c = ma->top;
  while (!0) {
    if (c->id == MEMALLOC_CHUNK_ID_FREE && c->size >= sz) {
      break;
    }
    if (c->next == 0) {
      return NULL;
    }
    c = next_chunk(c);
  }
  if (c->size > sizeof (MemAllocChunk) + sz) {
    MemAllocChunk *c2 = (MemAllocChunk *)(((int8_t *) c) + sizeof (MemAllocChunk) + sz);
    c2->id = MEMALLOC_CHUNK_ID_FREE;
    c2->size = c->size - sizeof (MemAllocChunk) - sz;
    c2->prev = sizeof (MemAllocChunk) + sz;
    c2->next = c->next;
    c->next = c2->prev;
  }
  c->id = MEMALLOC_CHUNK_ID_USED;
  c->size = sz;
  //print_map(ma);
  return ((int8_t *) c) + sizeof (MemAllocChunk);
}

void MemAllocFree(MemAlloc *ma, void *addr)
{
  MemAllocChunk *c;

  assert(ma != NULL);
  if (addr == NULL) {
    return;
  }
  c = (MemAllocChunk *)(((int8_t *) addr) - sizeof (MemAllocChunk));
  c->id = MEMALLOC_CHUNK_ID_FREE;
  if (c->next != 0) {
    MemAllocChunk *nc = next_chunk(c);
    if (nc->id == MEMALLOC_CHUNK_ID_FREE) {
      c->size += sizeof (MemAllocChunk) + nc->size;
      c->next = nc->next;
    }
  }
  if (c->prev != 0) {
    MemAllocChunk *pc = prev_chunk(c);
    if (pc->id == MEMALLOC_CHUNK_ID_FREE) {
      pc->size += sizeof (MemAllocChunk) + c->size;
      pc->next = c->next;
    }
  }
  //print_map(ma);
}

size_t MemAllocGetMaxFreeSize(MemAlloc *ma)
{
  size_t max_size;
  MemAllocChunk *c = ma->top;

  assert(ma != NULL);
  max_size = 0;
  while (!0) {
    if (c->id == MEMALLOC_CHUNK_ID_FREE && c->size > max_size) {
      max_size = c->size;
    }
    if (c->next == 0) {
      break;
    }
    c = next_chunk(c);
  }
  return max_size;
}
