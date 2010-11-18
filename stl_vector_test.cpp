#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <vector>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class StlVectorTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(StlVectorTest);
  CPPUNIT_TEST(test_begin);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_begin();
};

void StlVectorTest::test_begin()
{
  std::vector<int> v;
  //CPPUNIT_ASSERT_EQUAL(0, *v.begin()); // Segmentation fault
}

CPPUNIT_TEST_SUITE_REGISTRATION(StlVectorTest);
