#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "lot_box.hpp"
#include <gtest/gtest.h>
#include <algorithm>

TEST(LotBoxTest, draw)
{
  LotBox<100, 1> lot_box(time(0));
  std::vector<bool> results;
  for (size_t i = 0; i < 100; ++i) {
    bool r = lot_box.draw();
    results.push_back(r);
  }
  EXPECT_EQ(static_cast<std::ptrdiff_t>(1), std::count(results.begin(), results.end(), true));
  results.clear();
  for (size_t i = 0; i < 200; ++i) {
    bool r = lot_box.draw();
    results.push_back(r);
  }
  EXPECT_EQ(static_cast<std::ptrdiff_t>(2), std::count(results.begin(), results.end(), true));
}
