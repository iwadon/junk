#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "memory_allocator.hpp"
#include <gtest/gtest.h>

TEST(MemoryAllocatorTest, allocate) {
  char buf[256];
  MemoryAllocator ma(buf, sizeof buf);
  ASSERT_EQ(ma.allocate(101), buf + 16);
  ASSERT_EQ(ma.allocate(51), buf + 16 + 104 + 16);
  ASSERT_TRUE(ma.allocate(100) == NULL);
  ASSERT_EQ(ma.allocate(51), buf + 16 + 104 + 16 + 52 + 16);
  ASSERT_TRUE(ma.allocate(1) == NULL);
}

TEST(MemoryAllocatorTest, allocate2) {
  char buf[16 + 4];
  MemoryAllocator ma(buf, sizeof buf);
  ASSERT_EQ(ma.allocate(1), buf + 16);
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
  char buf[256];
  MemoryAllocator ma(buf, sizeof buf);
  ma.allocate(101);
  ASSERT_EQ(120U, ma.max_free_size());
  ma.allocate(51);
  ASSERT_EQ(52U, ma.max_free_size());
  ma.allocate(51);
  ASSERT_EQ(0U, ma.max_free_size());
  ma.allocate(19);
  ASSERT_EQ(0U, ma.max_free_size());
}
