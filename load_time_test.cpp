#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "load_time.hpp"
#include <gtest/gtest.h>

#define ASSERT_TIME(a, b) {						\
    static const double base = LoadTime::TIME_BASE_SEC;			\
    static const double base_ms = LoadTime::TIME_BASE_MILLISEC;		\
    EXPECT_NEAR(a, b / base, 1.0 / (base / base_ms) * (1000.0 / 60));	\
  }

TEST(LoadTimeTest, elapsed_time)
{
  LoadTime lt;
  lt.activate(0);
  lt.start(0);
  usleep(10000);
  lt.stop(0);
  lt.flip();
  ASSERT_TIME(0.01f, lt.elapsed_time(0));
}

TEST(LoadTimeTest, activate)
{
  LoadTime lt;
  lt.start(0); usleep(10000); lt.stop(0);
  lt.start(1); usleep(10000); lt.stop(1);
  lt.flip();
  ASSERT_TIME(0.0, lt.elapsed_time(0));
  ASSERT_TIME(0.0, lt.elapsed_time(1));
  lt.activate(0);
  lt.start(0); usleep(10000); lt.stop(0);
  lt.start(1); usleep(10000); lt.stop(1);
  lt.flip();
  ASSERT_TIME(0.01, lt.elapsed_time(0));
  ASSERT_TIME(0.0, lt.elapsed_time(1));
  lt.activate(1);
  lt.start(0); usleep(10000); lt.stop(0);
  lt.start(1); usleep(10000); lt.stop(1);
  lt.flip();
  ASSERT_TIME(0.01, lt.elapsed_time(0));
  ASSERT_TIME(0.01, lt.elapsed_time(1));
}
