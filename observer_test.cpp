#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "observer.hpp"
#include <gtest/gtest.h>

static int n = 0;

class TestObserver : public Observer
{
public:
  void update(Subject */*subject*/)
  {
    ++n;
  }
};

TEST(ObserverTest, notify)
{
  Subject s;
  TestObserver o;
  n = 0;
  s.notify();
  EXPECT_EQ(0, n);
  s.attach(&o);
  s.notify();
  EXPECT_EQ(1, n);
  s.detach(&o);
  s.notify();
  EXPECT_EQ(1, n);
}
