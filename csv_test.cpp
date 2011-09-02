#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

int parse_integer(int &value, const char *str, const size_t len)
{
  const char *p = str;
  const char *end = str + len;
  if (p >= end) {
    return 0;
  }
  if (!isdigit(*p)) {
    return 0;
  }
  int v = 0;
  while (p < end) {
    v *= 10;
    v += *p - '0';
    ++p;
    if (!isdigit(*p)) {
      break;
    }
  }
  value = v;
  return p - str;
}

int skip_comma(const char *str, const size_t len)
{
  const char *p = str;
  const char *end = str + len;
  if (p >= end) {
    return 0;
  }
  return *p == ',' ? 1 : 0;
}

class CSVTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(CSVTest);
  CPPUNIT_TEST(test_parse_integer);
  CPPUNIT_TEST(test_skip_comma);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_parse_integer();
  void test_skip_comma();
};

void CSVTest::test_parse_integer()
{
  int i;

  CPPUNIT_ASSERT_EQUAL(0, parse_integer(i, "", 0));

  CPPUNIT_ASSERT_EQUAL(1, parse_integer(i, "7", 1));
  CPPUNIT_ASSERT_EQUAL(7, i);
  CPPUNIT_ASSERT_EQUAL(3, parse_integer(i, "765", 3));
  CPPUNIT_ASSERT_EQUAL(765, i);

  CPPUNIT_ASSERT_EQUAL(1, parse_integer(i, "7,65", 4));
  CPPUNIT_ASSERT_EQUAL(7, i);
}

void CSVTest::test_skip_comma()
{
  CPPUNIT_ASSERT_EQUAL(0, skip_comma("", 0));
  CPPUNIT_ASSERT_EQUAL(1, skip_comma(",", 1));
  CPPUNIT_ASSERT_EQUAL(0, skip_comma("0,", 2));
}

CPPUNIT_TEST_SUITE_REGISTRATION(CSVTest);
