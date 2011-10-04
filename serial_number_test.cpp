#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <gtest/gtest.h>

// http://tools.ietf.org/html/rfc1982
template <typename T, size_t BITS>
struct SerialNumber
{
  T value;
  SerialNumber(const T &x) : value(x) {}
  operator T() const { return value; }
  bool operator==(const T &x) const { return value == x; }
  bool operator!=(const T &x) const { return value != x; }
  bool operator<(const T &x) const { return (value < x && static_cast<size_t>(x - value) < (1 << (BITS - 1))) || (value > x && static_cast<size_t>(value - x) > (1 << (BITS - 1))); }
  bool operator>(const T &x) const { return (value < x && static_cast<size_t>(x - value) > (1 << (BITS - 1))) || (value > x && static_cast<size_t>(value - x) < (1 << (BITS - 1))); }
};

TEST(SerialNumberTest, GT) {
  SerialNumber<int, 4> sn(10);
  EXPECT_TRUE(sn <   0);
  EXPECT_TRUE(sn <   1);
  EXPECT_TRUE(sn !=  2);
  EXPECT_TRUE(sn >   3);
  EXPECT_TRUE(sn >   4);
  EXPECT_TRUE(sn >   5);
  EXPECT_TRUE(sn >   6);
  EXPECT_TRUE(sn >   7);
  EXPECT_TRUE(sn >   8);
  EXPECT_TRUE(sn >   9);
  EXPECT_TRUE(sn == 10);
  EXPECT_TRUE(sn <  11);
  EXPECT_TRUE(sn <  12);
  EXPECT_TRUE(sn <  13);
  EXPECT_TRUE(sn <  14);
  EXPECT_TRUE(sn <  15);
}
