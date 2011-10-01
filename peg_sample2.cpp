#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "peg.hpp"
#include <gtest/gtest.h>
#include <string>
#include <stack>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

namespace {
  std::stack<int> stack;
  void INT(const char *beg, const char *end) {
    std::string s(beg, end);
    int i = boost::lexical_cast<int>(s);
    stack.push(i);
  }
  void ADD(const char *, const char *) {
    int a = stack.top();
    stack.pop();
    int b = stack.top();
    stack.pop();
    int c = b + a;
    stack.push(c);
  }
  void SUB(const char *, const char *) {
    int a = stack.top();
    stack.pop();
    int b = stack.top();
    stack.pop();
    int c = b - a;
    stack.push(c);
  }
  void MUL(const char *, const char *) {
    int a = stack.top();
    stack.pop();
    int b = stack.top();
    stack.pop();
    int c = b * a;
    stack.push(c);
  }
  void DIV(const char *, const char *) {
    int a = stack.top();
    stack.pop();
    int b = stack.top();
    stack.pop();
    int c = b / a;
    stack.push(c);
  }
};

#define EXPECT_EXPR_EQ(a, b) {			\
    peg::Result result = peg::parse(Expr, (b));	\
    EXPECT_TRUE(result.status);			\
    EXPECT_STREQ("", result.rest);		\
    EXPECT_EQ(1U, stack.size());		\
    EXPECT_EQ((a), stack.top());		\
    while (!stack.empty()) {			\
      stack.pop();				\
    }						\
  }

/*
 * http://en.wikipedia.org/wiki/Parsing_expression_grammar
 *
 * Value   ← [0-9]+ / '(' Expr ')'
 * Product ← Value (('*' / '/') Value)*
 * Sum     ← Product (('+' / '-') Product)*
 * Expr    ← Sum
 */
TEST(PegSample2, Calc) {
  peg::Rule Value, Product, Sum, Expr;
  Value = (+peg::class_("[0-9]"))[&INT] / (peg::char_('(') >> Expr >> peg::char_(')'));
  Product = Value >> *((peg::char_('*') >> Value)[&MUL] / (peg::char_('/') >> Value)[&DIV]);
  Sum = Product >> *((peg::char_('+') >> Product)[&ADD] / (peg::char_('-') >> Product)[&SUB]);
  Expr = Sum;

  EXPECT_EXPR_EQ(  12, "12");
  EXPECT_EXPR_EQ(  15, "12+3");
  EXPECT_EXPR_EQ(   9, "12-3");
  EXPECT_EXPR_EQ(  36, "12*3");
  EXPECT_EXPR_EQ(   4, "12/3");
  EXPECT_EXPR_EQ(   7, "1+2*3");
  EXPECT_EXPR_EQ(   9, "(1+2)*3");
  EXPECT_EXPR_EQ( 352, "12*34-56");
  EXPECT_EXPR_EQ(-264, "12*(34-56)");
}
