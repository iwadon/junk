#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "peg.hpp"
#include <gtest/gtest.h>
#include <string>
#include <stack>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

struct A
{
  std::stack<int> stack_;

  void push(const char *b, const char *e);
  void add(const char *b, const char *e);
};

void A::push(const char *b, const char *e)
{
  std::string s(b, e);
  int x = strtol(s.c_str(), NULL, 10);
  stack_.push(x);
}

void A::add(const char *b, const char *e)
{
  int x = stack_.top();
  stack_.pop();
  int y = stack_.top();
  stack_.pop();
  stack_.push(x + y);
}

TEST(PegSample2, blank)
{
  peg::Rule blank = peg::char_(' ') / peg::char_('\t');
  peg::Result result;

  result = peg::parse(blank, " ");
  EXPECT_TRUE(result.status);
  result = peg::parse(blank, "\t");
  EXPECT_TRUE(result.status);
  result = peg::parse(blank, "a");
  EXPECT_FALSE(result.status);
}

TEST(PegSample2, expr)
{
  peg::Rule blank = peg::char_(' ') / peg::char_('\t');
  peg::Rule expr = *blank >> peg::str("hello");
  peg::Result result;

  result = peg::parse(expr, "hello");
  EXPECT_TRUE(result.status);
  result = peg::parse(expr, "bye");
  EXPECT_FALSE(result.status);
}

TEST(PegSample2, reserved_words)
{
  peg::Rule reserved_words = peg::str("hello") / peg::str("world");
  peg::Result result;

  result = peg::parse(reserved_words, "hello");
  EXPECT_TRUE(result.status);
  result = peg::parse(reserved_words, "world");
  EXPECT_TRUE(result.status);
  result = peg::parse(reserved_words, "bye");
  EXPECT_FALSE(result.status);
}

TEST(PegSample2, exprAction)
{
  peg::Rule integer = +peg::class_("0-9");
  A a;
  peg::Rule expr = (integer[boost::bind(&A::push, &a, _1, _2)] >> peg::char_('+') >> integer[boost::bind(&A::push, &a, _1, _2)])[boost::bind(&A::add, &a, _1, _2)];
  peg::Result result;

  result = peg::parse(expr, "1+2");
  EXPECT_TRUE(result.status);
  ASSERT_FALSE(a.stack_.empty());
  int i = a.stack_.top();
  EXPECT_EQ(3, i);
}

TEST(PegSample2, Class)
{
  peg::Rule Class, Range, Char;
  Class = peg::char_('[') >> *(!peg::char_(']') >> Range) >> peg::char_(']');
  Range = (Char >> peg::char_('-') >> Char) / Char;
  Char = peg::char_('\\') >> (peg::char_('a') / peg::char_('b') / peg::char_('e') / peg::char_('f') / peg::char_('n') / peg::char_('r') / peg::char_('t') / peg::char_('v') / peg::char_('\'') / peg::char_('"') / peg::char_('[') / peg::char_(']') / peg::char_('\\'));
  //Char = !peg::char_('\\') >> peg::any;
  peg::Result result;

  result = peg::parse(Class, "[]");
  EXPECT_TRUE(result.status);
  EXPECT_STREQ("", result.rest);

  result = peg::parse(Class, "[\\a\\b\\e\\f\\n\\r\\t\\v\\\'\\\"\\[\\]\\\\]");
  EXPECT_TRUE(result.status);
  EXPECT_STREQ("", result.rest);

  //result = peg::parse(Class, "[a-b]");
  //EXPECT_TRUE(result.status);
  //EXPECT_STREQ("", result.rest);
}
