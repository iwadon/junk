#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "memory_allocator.hpp"
#include <gtest/gtest.h>

TEST(MemoryAllocatorTest, allocate) {
  char buf[256];
  MemoryAllocator ma(buf, sizeof buf);
  ASSERT_EQ(ma.allocate(101), buf + MemoryAllocator::PADDING_SIZE);
  ASSERT_EQ(ma.allocate(51), buf + MemoryAllocator::PADDING_SIZE + 104 + MemoryAllocator::PADDING_SIZE);
  ASSERT_TRUE(ma.allocate(100) == NULL);
  ASSERT_EQ(ma.allocate(51), buf + MemoryAllocator::PADDING_SIZE + 104 + MemoryAllocator::PADDING_SIZE + 52 + MemoryAllocator::PADDING_SIZE);
  ASSERT_TRUE(ma.allocate(1) == NULL);
}

TEST(MemoryAllocatorTest, free) {
  char buf[256];
  MemoryAllocator ma(buf, sizeof buf);

  ASSERT_EQ(240U, ma.max_free_size());
  void *p = ma.allocate(100);
  ASSERT_EQ(124U, ma.max_free_size());
  ma.free(p);
  ASSERT_EQ(240U, ma.max_free_size());

  void *p1 = ma.allocate(100);
  ASSERT_EQ(124U, ma.max_free_size());
  void *p2 = ma.allocate(100);
  ASSERT_EQ(8U, ma.max_free_size());
  ma.free(p2);
  ASSERT_EQ(124U, ma.max_free_size());
  ma.free(p1);
  ASSERT_EQ(240U, ma.max_free_size());

  p1 = ma.allocate(100);
  ASSERT_EQ(124U, ma.max_free_size());
  p2 = ma.allocate(100);
  ASSERT_EQ(8U, ma.max_free_size());
  ma.free(p1);
  ASSERT_EQ(100U, ma.max_free_size());
  ma.free(p2);
  ASSERT_EQ(240U, ma.max_free_size());
}

TEST(MemoryAllocatorTest, max_free_size) {
  char buf[256 + MemoryAllocator::PADDING_SIZE];
  MemoryAllocator ma(buf, sizeof buf);
  ma.allocate(101);
  ASSERT_EQ(136U, ma.max_free_size());
  ma.allocate(51);
  ASSERT_EQ(68U, ma.max_free_size());
  ma.allocate(53);
  ASSERT_EQ(0U, ma.max_free_size());
  ma.allocate(19);
  ASSERT_EQ(0U, ma.max_free_size());
}
