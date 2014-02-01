#include <gtest/gtest.h>

class MemoryPool
{
public:
  void *Allocate();
};

TEST(MemoryPoolTest, Allocate)
{
  MemoryPool pool;
  auto ptr = pool.Allocate();
}
