#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "peg.hpp"

class PegTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(PegTest);
  CPPUNIT_TEST(test_parse);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_parse();
private:
};

static std::string str_;

static void action1(const char *first, const char *last)
{
  std::string s(first, last);
  str_ = s;
}

void PegTest::test_parse()
{
  peg::Result result;

  result = (peg::any[action1]).parse("foo");
  CPPUNIT_ASSERT_EQUAL(true, result.status);
  CPPUNIT_ASSERT_EQUAL(std::string("oo"), std::string(result.rest));
  CPPUNIT_ASSERT_EQUAL(std::string("f"), str_);
}

CPPUNIT_TEST_SUITE_REGISTRATION(PegTest);
