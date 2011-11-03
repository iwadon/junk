#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "object_counter.hpp"
#include "gtest/gtest.h"
#include <boost/shared_ptr.hpp>

class TestObject : ObjectCounter<TestObject>
{
};

TEST(ObjectCounterTest, created) {
  EXPECT_EQ(0, ObjectCounter<TestObject>::created);
  {
    boost::shared_ptr<TestObject> t1(new TestObject);
    EXPECT_EQ(1, ObjectCounter<TestObject>::created);
    {
      boost::shared_ptr<TestObject> t2(new TestObject);
      EXPECT_EQ(2, ObjectCounter<TestObject>::created);
    }
    EXPECT_EQ(2, ObjectCounter<TestObject>::created);
  }
  EXPECT_EQ(2, ObjectCounter<TestObject>::created);
}

TEST(ObjectCounterTest, alive) {
  EXPECT_EQ(0, ObjectCounter<TestObject>::alive);
  {
    boost::shared_ptr<TestObject> t1(new TestObject);
    EXPECT_EQ(1, ObjectCounter<TestObject>::alive);
    {
      boost::shared_ptr<TestObject> t2(new TestObject);
      EXPECT_EQ(2, ObjectCounter<TestObject>::alive);
    }
    EXPECT_EQ(1, ObjectCounter<TestObject>::alive);
  }
  EXPECT_EQ(0, ObjectCounter<TestObject>::alive);
}
