#include "memory_pool.hpp"
#include <gtest/gtest.h>

TEST(MemoryPoolTest, Allocate)
{
  MemoryPool<16> pool;
  auto ptr = pool.Allocate();
}
