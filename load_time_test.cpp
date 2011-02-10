#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "load_time.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class LoadTimeTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(LoadTimeTest);
  CPPUNIT_TEST(test_add_item);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_add_item();
};

void LoadTimeTest::test_add_item()
{
  LoadTime lt;
}

CPPUNIT_TEST_SUITE_REGISTRATION(LoadTimeTest);
