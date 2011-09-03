#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "peg.hpp"
#include <gtest/gtest.h>

static std::string str_;

static void action1(const char *first, const char *last)
{
  std::string s(first, last);
  str_ = s;
}

#define PEG_ASSERT(PEG, STATUS, MATCHED, REST) {			\
    str_.clear();							\
    peg::Result result = PEG;						\
    EXPECT_EQ(std::string(REST), std::string(result.rest));	\
    EXPECT_EQ(std::string(MATCHED), str_);			\
    EXPECT_EQ(STATUS, result.status);			\
  }

#define PEG_ASSERT2(PEG, SRC, STATUS, MATCHED, REST) {	\
    str_.clear();					\
    peg::Result result = peg::parse(PEG, SRC);		\
    EXPECT_EQ(STATUS, result.status);			\
    EXPECT_STREQ(REST, result.rest);			\
    EXPECT_STREQ(MATCHED, str_.c_str());		\
  }

TEST(PegTest, inspect)
{
  // any
  EXPECT_EQ(std::string("#<peg::Any>"), peg::any.inspect());

  // char_
  EXPECT_EQ(std::string("#<peg::Char 'a'>"), peg::char_('a').inspect());
  EXPECT_EQ(std::string("#<peg::Char '\\xEF'>"), peg::char_(0xef).inspect());
  EXPECT_EQ(std::string("#<peg::Char '\\x12'>"), peg::char_(0x12).inspect());

  // string
  EXPECT_EQ(std::string("#<peg::String \"abc\">"), peg::str("abc").inspect());
  EXPECT_EQ(std::string("#<peg::String \"\\x12\\xEF\\x20'\"\\t\\r\\n\">"), peg::str("\x12\xef '\"\t\r\n").inspect());

  // class
  EXPECT_EQ(std::string("#<peg::Class a>"), peg::class_("a").inspect());
  EXPECT_EQ(std::string("#<peg::Class 0-9>"), peg::class_("0-9").inspect());
  EXPECT_EQ(std::string("#<peg::Class a-zA-Z0-9_>"), peg::class_("a-zA-Z0-9_").inspect());

  // sequence
  EXPECT_EQ(std::string("#<peg::Sequence #<peg::Char 'a'>, #<peg::Any>>"), (peg::char_('a') >> peg::any).inspect());

  // ordered choice
  EXPECT_EQ(std::string("#<peg::OrderedChoice #<peg::Char 'a'>, #<peg::Char 'b'>>"), (peg::char_('a') / peg::char_('b')).inspect());

  // zero-or-more
  EXPECT_EQ(std::string("#<peg::ZeroOrMore #<peg::Char 'a'>>"), (*peg::char_('a')).inspect());

  // one-or-more
  EXPECT_EQ(std::string("#<peg::OneOrMore #<peg::Char 'a'>>"), (+peg::char_('a')).inspect());

  // optional
  EXPECT_EQ(std::string("#<peg::Optional #<peg::Char 'a'>>"), (-peg::char_('a')).inspect());

  // and-predicate
  EXPECT_EQ(std::string("#<peg::AndPredicate #<peg::Char 'a'>>"), (&peg::char_('a')).inspect());

  // not-predicate
  EXPECT_EQ(std::string("#<peg::NotPredicate #<peg::Char 'a'>>"), (!peg::char_('a')).inspect());

  // rule
  peg::Rule pe = peg::char_('a');
  EXPECT_EQ(std::string("#<peg::Rule #<peg::Char 'a'>>"), pe.inspect());

  // result
  peg::Result result = peg::parse(peg::any, "abc");
  EXPECT_EQ(std::string("#<peg::Result OK \"bc\">"), result.inspect());
  result = peg::parse(!peg::any, "abc");
  EXPECT_EQ(std::string("#<peg::Result NG \"abc\">"), result.inspect());
}

TEST(PegTest, str)
{
  peg::Rule r;

  // any
  EXPECT_EQ(std::string("."), peg::any.str());

  // byte
  EXPECT_EQ(std::string("[4B]"), peg::byte(4).str());

  // char_
  EXPECT_EQ(std::string("'a'"), peg::char_('a').str());

  // string
  EXPECT_EQ(std::string("\"abc\""), peg::str("abc").str());

  // class
  EXPECT_EQ(std::string("[a]"), peg::class_("a").str());
  EXPECT_EQ(std::string("[0-9]"), peg::class_("0-9").str());
  EXPECT_EQ(std::string("[a-zA-Z0-9_]"), peg::class_("a-zA-Z0-9_").str());

  // sequence
  EXPECT_EQ(std::string("'a' 'b'"), (peg::char_('a') >> peg::char_('b')).str());
  EXPECT_EQ(std::string("'a' 'b' 'c'"), (peg::char_('a') >> peg::char_('b') >> peg::char_('c')).str());
  //EXPECT_EQ(std::string("'a' 'b' 'c'"), (peg::char_('a') / peg::char_('b') >> peg::char_('c')).str());

  // ordered choice
  EXPECT_EQ(std::string("'a' / 'b'"), (peg::char_('a') / peg::char_('b')).str());
  EXPECT_EQ(std::string("'a' / 'b' / 'c'"), (peg::char_('a') / peg::char_('b') / peg::char_('c')).str());

  // zero-or-more
  EXPECT_EQ(std::string(".*"), (*peg::any).str());
  EXPECT_EQ(std::string("[4B]*"), (*peg::byte(4)).str());
  EXPECT_EQ(std::string("'a'*"), (*peg::char_('a')).str());
  EXPECT_EQ(std::string("\"abc\"*"), (*peg::str("abc")).str());
  EXPECT_EQ(std::string("[0-9]*"), (*peg::class_("0-9")).str());
  EXPECT_EQ(std::string("('a' 'b')*"), (*(peg::char_('a') >> peg::char_('b'))).str());
  EXPECT_EQ(std::string("('a' / 'b')*"), (*(peg::char_('a') / peg::char_('b'))).str());
  EXPECT_EQ(std::string("(.*)*"), (*(*peg::any)).str());
  EXPECT_EQ(std::string("(.+)*"), (*(+peg::any)).str());
  EXPECT_EQ(std::string("(.?)*"), (*(-peg::any)).str());
  EXPECT_EQ(std::string("(&.)*"), (*(&peg::any)).str());
  EXPECT_EQ(std::string("(!.)*"), (*(!peg::any)).str());
  r = peg::any;
  EXPECT_EQ(std::string(".*"), (*r).str());
  r = peg::any >> peg::any;
  EXPECT_EQ(std::string("(. .)*"), (*r).str());

  // one-or-more
  EXPECT_EQ(std::string(".+"), (+peg::any).str());
  EXPECT_EQ(std::string("[4B]+"), (+peg::byte(4)).str());
  EXPECT_EQ(std::string("'a'+"), (+peg::char_('a')).str());
  EXPECT_EQ(std::string("\"abc\"+"), (+peg::str("abc")).str());
  EXPECT_EQ(std::string("[0-9]+"), (+peg::class_("0-9")).str());
  EXPECT_EQ(std::string("('a' 'b')+"), (+(peg::char_('a') >> peg::char_('b'))).str());
  EXPECT_EQ(std::string("('a' / 'b')+"), (+(peg::char_('a') / peg::char_('b'))).str());
  EXPECT_EQ(std::string("(.*)+"), (+(*peg::any)).str());
  EXPECT_EQ(std::string("(.+)+"), (+(+peg::any)).str());
  EXPECT_EQ(std::string("(.?)+"), (+(-peg::any)).str());
  EXPECT_EQ(std::string("(&.)+"), (+(&peg::any)).str());
  EXPECT_EQ(std::string("(!.)+"), (+(!peg::any)).str());
  r = peg::any;
  EXPECT_EQ(std::string(".+"), (+r).str());
  r = peg::any >> peg::any;
  EXPECT_EQ(std::string("(. .)+"), (+r).str());

  // optional
  EXPECT_EQ(std::string("'a'?"), (-peg::char_('a')).str());

  // and-predicate
  EXPECT_EQ(std::string("&'a'"), (&peg::char_('a')).str());

  // not-predicate
  EXPECT_EQ(std::string("!'a'"), (!peg::char_('a')).str());

  // rule
  peg::Rule a_or_b = peg::char_('a') / peg::char_('b');
  EXPECT_EQ(std::string("'a' / 'b'"), a_or_b.str());
}

TEST(PegTest, parse)
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

  // class
  PEG_ASSERT2(peg::class_("a")[action1], "abc", true, "a", "bc");
  PEG_ASSERT2(peg::class_("a-c")[action1], "b", true, "b", "");
  PEG_ASSERT2(peg::class_("a-c")[action1], "d", false, "", "d");
  PEG_ASSERT2(peg::class_("a-zA-Z0-9_")[action1], "5", true, "5", "");
  PEG_ASSERT2(peg::class_("a-zA-Z0-9_")[action1], "@", false, "", "@");

  // sequence
  PEG_ASSERT(peg::parse((peg::char_('f') >> peg::char_('o'))[action1], "foo"), true, "fo", "o");
  PEG_ASSERT(peg::parse((peg::char_('b') >> peg::char_('o'))[action1], "bar"), false, "", "bar");

  // ordered choice
  PEG_ASSERT(peg::parse((peg::char_('f') / peg::char_('b'))[action1], "foo"), true, "f", "oo");
  PEG_ASSERT(peg::parse((peg::char_('f') / peg::char_('b'))[action1], "bar"), true, "b", "ar");
  PEG_ASSERT(peg::parse((peg::char_('a') / peg::char_('z'))[action1], "baz"), false, "", "baz");
  PEG_ASSERT(peg::parse(((peg::char_('a') >> peg::char_('b')) / (peg::char_('a') >> peg::char_('c')))[action1], "abc"), true, "ab", "c");
  PEG_ASSERT(peg::parse(((peg::char_('a') >> peg::char_('b')) / (peg::char_('a') >> peg::char_('c')))[action1], "acd"), true, "ac", "d");

  // (a / b) c
  PEG_ASSERT2((peg::char_('a') / peg::char_('b') >> peg::char_('c'))[action1], "acbc", true, "ac", "bc");
  // a (b / c)
  PEG_ASSERT2((peg::char_('a') >> peg::char_('b') / peg::char_('c'))[action1], "ab", true, "ab", "");
  PEG_ASSERT2((peg::char_('a') >> peg::char_('b') / peg::char_('c'))[action1], "ac", true, "ac", "");
  // (a b) / c
  PEG_ASSERT2(((peg::char_('a') >> peg::char_('b')) / peg::char_('c'))[action1], "ab", true, "ab", "");
  PEG_ASSERT2(((peg::char_('a') >> peg::char_('b')) / peg::char_('c'))[action1], "c", true, "c", "");

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
  PEG_ASSERT(peg::parse(!peg::any, ""), true, "", "");

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
TEST(PegTest, example_1)
{
  peg::Rule value, product, sum, expr;
  value = (+peg::class_("0-9")) / (peg::char_('(') >> expr >> peg::char_(')'));
  product = value >> *((peg::char_('*') / peg::char_('/')) >> value);
  sum = product >> *((peg::char_('+') / peg::char_('-')) >> product);
  expr = sum;
  PEG_ASSERT(peg::parse(expr[action1], "(123+456)*789"), true, "(123+456)*789", "");
}
