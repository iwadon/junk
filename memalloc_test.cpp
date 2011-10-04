#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "memalloc.h"
#include <gtest/gtest.h>

TEST(MemAllocTest, allocate) {
  char buf[256];
  MemAlloc ma;
  MemAllocInitialize(&ma, buf, sizeof buf);
  ASSERT_EQ(MemAllocAllocate(&ma, 101), buf + 16);
  ASSERT_EQ(MemAllocAllocate(&ma, 51), buf + 16 + 104 + 16);
  ASSERT_EQ(52U, MemAllocGetMaxFreeSize(&ma));
  ASSERT_TRUE(MemAllocAllocate(&ma, 100) == NULL);
  ASSERT_EQ(MemAllocAllocate(&ma, 51), buf + 16 + 104 + 16 + 52 + 16);
  ASSERT_TRUE(MemAllocAllocate(&ma, 1) == NULL);
}

TEST(MemAllocTest, allocate2) {
  char buf[16 + 4];
  MemAlloc ma;
  MemAllocInitialize(&ma, buf, sizeof buf);
  ASSERT_EQ(MemAllocAllocate(&ma, 1), buf + 16);
}

TEST(MemAllocTest, free) {
  char buf[256];
  MemAlloc ma;
  MemAllocInitialize(&ma, buf, sizeof buf);

  ASSERT_EQ(240U, MemAllocGetMaxFreeSize(&ma));
  void *p = MemAllocAllocate(&ma, 100);
  ASSERT_EQ(124U, MemAllocGetMaxFreeSize(&ma));
  MemAllocFree(&ma, p);
  ASSERT_EQ(240U, MemAllocGetMaxFreeSize(&ma));

  void *p1 = MemAllocAllocate(&ma, 100);
  ASSERT_EQ(124U, MemAllocGetMaxFreeSize(&ma));
  void *p2 = MemAllocAllocate(&ma, 100);
  ASSERT_EQ(8U, MemAllocGetMaxFreeSize(&ma));
  MemAllocFree(&ma, p2);
  ASSERT_EQ(124U, MemAllocGetMaxFreeSize(&ma));
  MemAllocFree(&ma, p1);
  ASSERT_EQ(240U, MemAllocGetMaxFreeSize(&ma));

  p1 = MemAllocAllocate(&ma, 100);
  ASSERT_EQ(124U, MemAllocGetMaxFreeSize(&ma));
  p2 = MemAllocAllocate(&ma, 100);
  ASSERT_EQ(8U, MemAllocGetMaxFreeSize(&ma));
  MemAllocFree(&ma, p1);
  ASSERT_EQ(100U, MemAllocGetMaxFreeSize(&ma));
  MemAllocFree(&ma, p2);
  ASSERT_EQ(240U, MemAllocGetMaxFreeSize(&ma));
}

TEST(MemAllocTest, max_free_size) {
  char buf[256];
  MemAlloc ma;
  MemAllocInitialize(&ma, buf, sizeof buf);
  MemAllocAllocate(&ma, 101);
  ASSERT_EQ(120U, MemAllocGetMaxFreeSize(&ma));
  MemAllocAllocate(&ma, 51);
  ASSERT_EQ(52U, MemAllocGetMaxFreeSize(&ma));
  MemAllocAllocate(&ma, 51);
  ASSERT_EQ(0U, MemAllocGetMaxFreeSize(&ma));
  MemAllocAllocate(&ma, 19);
  ASSERT_EQ(0U, MemAllocGetMaxFreeSize(&ma));
}
