#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "volume.hpp"
#include <gtest/gtest.h>

TEST(VolumeTest, is_updated)
{
  Volume<float, int32_t> v(0.0f);
  EXPECT_EQ(false, v.is_updated());
  v.update();
  EXPECT_EQ(false, v.is_updated());
  v.set(1.0f);
  EXPECT_EQ(false, v.is_updated());
  v.update();
  EXPECT_EQ(true, v.is_updated());
  v.update();
  EXPECT_EQ(false, v.is_updated());
  v.set(2.0f, 2);
  v.update();
  EXPECT_EQ(true, v.is_updated());
  v.update();
  EXPECT_EQ(true, v.is_updated());
  v.update();
  EXPECT_EQ(false, v.is_updated());
}

TEST(VolumeTest, set)
{
  Volume<float, int32_t> v(0.0f);
  v.set(1.0f);
  EXPECT_EQ(1.0f, v.get());
  v.set(2.0f, 1);
  EXPECT_EQ(1.0f, v.get());
  v.update();
  EXPECT_EQ(2.0f, v.get());
}

TEST(VolumeTest, update)
{
  Volume<float, int32_t> v(0.0f);
  v.set(1.0f, 2);
  EXPECT_EQ(0.0f, v.get());
  v.update();
  EXPECT_EQ(0.5f, v.get());
  v.update();
  EXPECT_EQ(1.0f, v.get());
  v.update();
  EXPECT_EQ(1.0f, v.get());
}
