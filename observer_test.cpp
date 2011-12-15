#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "observer.hpp"
#include <gtest/gtest.h>

static int n = 0;

class TestSubject;

class TestObserver : public Observer<TestSubject>
{
public:
  void update(Subject<TestSubject> */*subject*/)
  {
    ++n;
  }
};

class TestSubject : public Subject<TestSubject>
{
};

TEST(ObserverTest, notify)
{
  TestSubject s;
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
