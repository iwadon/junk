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

#define PEG_ASSERT(PEG, STATUS, MATCHED, REST) {			\
    peg::Result result = PEG;						\
    CPPUNIT_ASSERT_EQUAL(std::string(REST), std::string(result.rest));	\
    CPPUNIT_ASSERT_EQUAL(std::string(MATCHED), str_);			\
    CPPUNIT_ASSERT_EQUAL(STATUS, result.status);			\
  }

void PegTest::test_parse()
{
  // any
  PEG_ASSERT((peg::any[action1]).parse("foo"), true, "f", "oo");

  // byte
  PEG_ASSERT((peg::byte(1)[action1]).parse("\x01\x23\x45\x67"), true, "\x01", "\x23\x45\x67");
  PEG_ASSERT((peg::byte(2)[action1]).parse("\x01\x23\x45\x67"), true, "\x01\x23", "\x45\x67");

  // char_
  PEG_ASSERT((peg::char_('f')[action1]).parse("foo"), true, "f", "oo");
  PEG_ASSERT((peg::char_('o')[action1]).parse("foo"), false, "", "foo");

  // ordered choice
  PEG_ASSERT((peg::char_('f') / peg::char_('b'))[action1].parse("foo"), true, "f", "oo");
  PEG_ASSERT((peg::char_('f') / peg::char_('b'))[action1].parse("bar"), true, "b", "ar");
}

CPPUNIT_TEST_SUITE_REGISTRATION(PegTest);
