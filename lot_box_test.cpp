#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "lot_box.hpp"
#include <algorithm>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class LotBoxTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(LotBoxTest);
  CPPUNIT_TEST(test_draw);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_draw();
};

void LotBoxTest::test_draw()
{
  LotBox<100, 1> lot_box(time(0));
  std::vector<bool> results;
  for (size_t i = 0; i < 100; ++i) {
    bool r = lot_box.draw();
    results.push_back(r);
  }
  CPPUNIT_ASSERT_EQUAL(static_cast<std::ptrdiff_t>(1), std::count(results.begin(), results.end(), true));
  results.clear();
  for (size_t i = 0; i < 200; ++i) {
    bool r = lot_box.draw();
    results.push_back(r);
  }
  CPPUNIT_ASSERT_EQUAL(static_cast<std::ptrdiff_t>(2), std::count(results.begin(), results.end(), true));
}

CPPUNIT_TEST_SUITE_REGISTRATION(LotBoxTest);
