#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "peg.hpp"

class PegTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(PegTest);
  CPPUNIT_TEST(test_inspect);
  CPPUNIT_TEST(test_parse);
  CPPUNIT_TEST(test_example_1);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_inspect();
  void test_parse();
  void test_example_1();
private:
};

static std::string str_;

static void action1(const char *first, const char *last)
{
  std::string s(first, last);
  str_ = s;
}

#define PEG_ASSERT(PEG, STATUS, MATCHED, REST) {			\
    str_.clear();							\
    peg::Result result = PEG;						\
    CPPUNIT_ASSERT_EQUAL(std::string(REST), std::string(result.rest));	\
    CPPUNIT_ASSERT_EQUAL(std::string(MATCHED), str_);			\
    CPPUNIT_ASSERT_EQUAL(STATUS, result.status);			\
  }

void PegTest::test_inspect()
{
  // any
  CPPUNIT_ASSERT_EQUAL(std::string("."), peg::any.inspect());

  // byte
  CPPUNIT_ASSERT_EQUAL(std::string("[4B]"), peg::byte(4).inspect());

  // char_
  CPPUNIT_ASSERT_EQUAL(std::string("'a'"), peg::char_('a').inspect());

  // string
  CPPUNIT_ASSERT_EQUAL(std::string("\"abc\""), peg::str("abc").inspect());

  // range
  CPPUNIT_ASSERT_EQUAL(std::string("[0-9]"), peg::range('0', '9').inspect());

  // sequence
  CPPUNIT_ASSERT_EQUAL(std::string("'a' 'b'"), (peg::char_('a') >> peg::char_('b')).inspect());

  // ordered choice
  CPPUNIT_ASSERT_EQUAL(std::string("'a' / 'b'"), (peg::char_('a') / peg::char_('b')).inspect());

  // zero-or-more
  CPPUNIT_ASSERT_EQUAL(std::string("'a'*"), (*peg::char_('a')).inspect());

  // one-or-more
  CPPUNIT_ASSERT_EQUAL(std::string("'a'+"), (+peg::char_('a')).inspect());

  // optional
  CPPUNIT_ASSERT_EQUAL(std::string("'a'?"), (-peg::char_('a')).inspect());

  // and-predicate
  CPPUNIT_ASSERT_EQUAL(std::string("&'a'"), (&peg::char_('a')).inspect());

  // not-predicate
  CPPUNIT_ASSERT_EQUAL(std::string("!'a'"), (!peg::char_('a')).inspect());

  // rule
  peg::Rule a_or_b = peg::char_('a') / peg::char_('b');
  CPPUNIT_ASSERT_EQUAL(std::string("'a' / 'b'"), a_or_b.inspect());
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

  // string
  PEG_ASSERT((peg::str("foo")[action1]).parse("foobarbaz"), true, "foo", "barbaz");
  PEG_ASSERT((peg::str("bar")[action1]).parse("foobarbaz"), false, "", "foobarbaz");

  // range
  PEG_ASSERT((peg::range('0', '3')[action1]).parse("123"), true, "1", "23");
  PEG_ASSERT(((+peg::range('0', '3'))[action1]).parse("135"), true, "13", "5");

  // sequence
  PEG_ASSERT((peg::char_('f') >> peg::char_('o'))[action1].parse("foo"), true, "fo", "o");
  PEG_ASSERT((peg::char_('b') >> peg::char_('o'))[action1].parse("bar"), false, "", "bar");

  // ordered choice
  PEG_ASSERT((peg::char_('f') / peg::char_('b'))[action1].parse("foo"), true, "f", "oo");
  PEG_ASSERT((peg::char_('f') / peg::char_('b'))[action1].parse("bar"), true, "b", "ar");
  PEG_ASSERT((peg::char_('a') / peg::char_('z'))[action1].parse("baz"), false, "", "baz");

  // zero-or-more
  PEG_ASSERT((*peg::char_('a'))[action1].parse("aabbcc"), true, "aa", "bbcc");
  PEG_ASSERT((*peg::char_('a'))[action1].parse("bbccdd"), true, "", "bbccdd");

  // one-or-more
  PEG_ASSERT((+peg::char_('a'))[action1].parse("aabbcc"), true, "aa", "bbcc");
  PEG_ASSERT((+peg::char_('a'))[action1].parse("bbccdd"), false, "", "bbccdd");

  // optional
  PEG_ASSERT((-peg::char_('a'))[action1].parse("aaa"), true, "a", "aa");
  PEG_ASSERT((+peg::char_('a'))[action1].parse("bbb"), false, "", "bbb");

  // and-predicate
  PEG_ASSERT((&peg::char_('a') >> +peg::any)[action1].parse("abc"), true, "abc", "");
  PEG_ASSERT((&peg::char_('a') >> +peg::any)[action1].parse("cba"), false, "", "cba");

  // not-predicate
  PEG_ASSERT((!peg::char_('a') >> +peg::any)[action1].parse("abc"), false, "", "abc");
  PEG_ASSERT((!peg::char_('a') >> +peg::any)[action1].parse("cba"), true, "cba", "");

  // rule
  peg::Rule a_or_b = (peg::char_('a') / peg::char_('b'))[action1];
  PEG_ASSERT(a_or_b.parse("abc"), true, "a", "bc");
  PEG_ASSERT(a_or_b.parse("cba"), false, "", "cba");
  peg::Rule c_or_d;
  c_or_d = (peg::char_('c') / peg::char_('d'))[action1];
  PEG_ASSERT(c_or_d.parse("dcb"), true, "d", "cb");
  PEG_ASSERT(c_or_d.parse("bcd"), false, "", "bcd");
}

/**
 * http://en.wikipedia.org/wiki/Parsing_expression_grammar#Examples
 *
 *   Value ← [0-9]+ / '(' Expr ')'
 *   Product ← Value (('*' / '/') Value)*
 *   Sum ← Product (('+' / '-') Product)*
 *   Expr ← Sum
 */
void PegTest::test_example_1()
{
  peg::Rule value, product, sum, expr;
  value = (+peg::range('0', '9')) / (peg::char_('(') >> expr >> peg::char_(')'));
  product = value >> *((peg::char_('*') / peg::char_('/')) >> value);
  sum = product >> *((peg::char_('+') / peg::char_('-')) >> product);
  expr = sum;
  PEG_ASSERT((expr[action1]).parse("(123+456)*789"), true, "(123+456)*789", "");
}

CPPUNIT_TEST_SUITE_REGISTRATION(PegTest);
