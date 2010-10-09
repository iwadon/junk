#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "peg.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class PegTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(PegTest);
  CPPUNIT_TEST(test_inspect);
  CPPUNIT_TEST(test_str);
  CPPUNIT_TEST(test_parse);
  CPPUNIT_TEST(test_example_1);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_inspect();
  void test_str();
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
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::Any>"), peg::any.inspect());

  // char_
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::Char 'a'>"), peg::char_('a').inspect());
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::Char '\\xEF'>"), peg::char_(0xef).inspect());
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::Char '\\x12'>"), peg::char_(0x12).inspect());

  // string
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::String \"abc\">"), peg::str("abc").inspect());
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::String \"\\x12\\xEF\\x20'\"\\t\\r\\n\">"), peg::str("\x12\xef '\"\t\r\n").inspect());

  // range
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::Range 'a'..'z'>"), peg::range('a', 'z').inspect());

  // sequence
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::Sequence #<peg::Char 'a'>, #<peg::Any>>"), (peg::char_('a') >> peg::any).inspect());

  // ordered choice
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::OrderedChoice #<peg::Char 'a'>, #<peg::Char 'b'>>"), (peg::char_('a') / peg::char_('b')).inspect());

  // zero-or-more
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::ZeroOrMore #<peg::Char 'a'>>"), (*peg::char_('a')).inspect());

  // one-or-more
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::OneOrMore #<peg::Char 'a'>>"), (+peg::char_('a')).inspect());

  // optional
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::Optional #<peg::Char 'a'>>"), (-peg::char_('a')).inspect());

  // and-predicate
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::AndPredicate #<peg::Char 'a'>>"), (&peg::char_('a')).inspect());

  // not-predicate
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::NotPredicate #<peg::Char 'a'>>"), (!peg::char_('a')).inspect());

  // rule
  peg::Rule pe = peg::char_('a');
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::Rule #<peg::Char 'a'>>"), pe.inspect());

  // result
  peg::Result result = peg::parse(peg::any, "abc");
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::Result OK \"bc\">"), result.inspect());
  result = peg::parse(!peg::any, "abc");
  CPPUNIT_ASSERT_EQUAL(std::string("#<peg::Result NG \"abc\">"), result.inspect());
}

void PegTest::test_str()
{
  // any
  CPPUNIT_ASSERT_EQUAL(std::string("."), peg::any.str());

  // byte
  CPPUNIT_ASSERT_EQUAL(std::string("[4B]"), peg::byte(4).str());

  // char_
  CPPUNIT_ASSERT_EQUAL(std::string("'a'"), peg::char_('a').str());

  // string
  CPPUNIT_ASSERT_EQUAL(std::string("\"abc\""), peg::str("abc").str());

  // range
  CPPUNIT_ASSERT_EQUAL(std::string("[0-9]"), peg::range('0', '9').str());

  // sequence
  CPPUNIT_ASSERT_EQUAL(std::string("'a' 'b'"), (peg::char_('a') >> peg::char_('b')).str());

  // ordered choice
  CPPUNIT_ASSERT_EQUAL(std::string("'a' / 'b'"), (peg::char_('a') / peg::char_('b')).str());

  // zero-or-more
  CPPUNIT_ASSERT_EQUAL(std::string("'a'*"), (*peg::char_('a')).str());

  // one-or-more
  CPPUNIT_ASSERT_EQUAL(std::string("'a'+"), (+peg::char_('a')).str());

  // optional
  CPPUNIT_ASSERT_EQUAL(std::string("'a'?"), (-peg::char_('a')).str());

  // and-predicate
  CPPUNIT_ASSERT_EQUAL(std::string("&'a'"), (&peg::char_('a')).str());

  // not-predicate
  CPPUNIT_ASSERT_EQUAL(std::string("!'a'"), (!peg::char_('a')).str());

  // rule
  peg::Rule a_or_b = peg::char_('a') / peg::char_('b');
  CPPUNIT_ASSERT_EQUAL(std::string("'a' / 'b'"), a_or_b.str());
}

void PegTest::test_parse()
{
  // any
  PEG_ASSERT(peg::parse(peg::any[action1], "foo"), true, "f", "oo");

  // byte
  PEG_ASSERT(peg::parse(peg::byte(1)[action1], "\x01\x23\x45\x67"), true, "\x01", "\x23\x45\x67");
  PEG_ASSERT(peg::parse(peg::byte(2)[action1], "\x01\x23\x45\x67"), true, "\x01\x23", "\x45\x67");

  // char_
  PEG_ASSERT(peg::parse(peg::char_('f')[action1], "foo"), true, "f", "oo");
  PEG_ASSERT(peg::parse(peg::char_('o')[action1], "foo"), false, "", "foo");

  // string
  PEG_ASSERT(peg::parse(peg::str("foo")[action1], "foobarbaz"), true, "foo", "barbaz");
  PEG_ASSERT(peg::parse(peg::str("bar")[action1], "foobarbaz"), false, "", "foobarbaz");

  // range
  PEG_ASSERT(peg::parse(peg::range('0', '3')[action1], "123"), true, "1", "23");
  PEG_ASSERT(peg::parse((+peg::range('0', '3'))[action1], "135"), true, "13", "5");

  // sequence
  PEG_ASSERT(peg::parse((peg::char_('f') >> peg::char_('o'))[action1], "foo"), true, "fo", "o");
  PEG_ASSERT(peg::parse((peg::char_('b') >> peg::char_('o'))[action1], "bar"), false, "", "bar");

  // ordered choice
  PEG_ASSERT(peg::parse((peg::char_('f') / peg::char_('b'))[action1], "foo"), true, "f", "oo");
  PEG_ASSERT(peg::parse((peg::char_('f') / peg::char_('b'))[action1], "bar"), true, "b", "ar");
  PEG_ASSERT(peg::parse((peg::char_('a') / peg::char_('z'))[action1], "baz"), false, "", "baz");
  PEG_ASSERT(peg::parse(((peg::char_('a') >> peg::char_('b')) / (peg::char_('a') >> peg::char_('c')))[action1], "abc"), true, "ab", "c");
  PEG_ASSERT(peg::parse(((peg::char_('a') >> peg::char_('b')) / (peg::char_('a') >> peg::char_('c')))[action1], "acd"), true, "ac", "d");

  // zero-or-more
  PEG_ASSERT(peg::parse((*peg::char_('a'))[action1], "aabbcc"), true, "aa", "bbcc");
  PEG_ASSERT(peg::parse((*peg::char_('a'))[action1], "bbccdd"), true, "", "bbccdd");

  // one-or-more
  PEG_ASSERT(peg::parse((+peg::char_('a'))[action1], "aabbcc"), true, "aa", "bbcc");
  PEG_ASSERT(peg::parse((+peg::char_('a'))[action1], "bbccdd"), false, "", "bbccdd");

  // optional
  PEG_ASSERT(peg::parse((-peg::char_('a'))[action1], "aaa"), true, "a", "aa");
  PEG_ASSERT(peg::parse((-peg::char_('a'))[action1], "bbb"), true, "", "bbb");
  PEG_ASSERT(peg::parse((-(peg::char_('a') >> peg::char_('b')))[action1], "acd"), true, "", "acd");

  // and-predicate
  PEG_ASSERT(peg::parse((&peg::char_('a') >> +peg::any)[action1], "abc"), true, "abc", "");
  PEG_ASSERT(peg::parse((&peg::char_('a') >> +peg::any)[action1], "cba"), false, "", "cba");

  // not-predicate
  PEG_ASSERT(peg::parse((!peg::char_('a') >> +peg::any)[action1], "abc"), false, "", "abc");
  PEG_ASSERT(peg::parse((!peg::char_('a') >> +peg::any)[action1], "cba"), true, "cba", "");

  // rule
  peg::Rule a_or_b = (peg::char_('a') / peg::char_('b'))[action1];
  PEG_ASSERT(peg::parse(a_or_b, "abc"), true, "a", "bc");
  PEG_ASSERT(peg::parse(a_or_b, "cba"), false, "", "cba");
  peg::Rule c_or_d;
  c_or_d = (peg::char_('c') / peg::char_('d'))[action1];
  PEG_ASSERT(peg::parse(c_or_d, "dcb"), true, "d", "cb");
  PEG_ASSERT(peg::parse(c_or_d, "bcd"), false, "", "bcd");
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
  PEG_ASSERT(peg::parse(expr[action1], "(123+456)*789"), true, "(123+456)*789", "");
}

CPPUNIT_TEST_SUITE_REGISTRATION(PegTest);
