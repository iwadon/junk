// PEG sample (working)
// Based on peg-0.1.4/peg.peg.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "peg.hpp"
#include <gtest/gtest.h>

class PegSample : public ::testing::Test
{
public:
  static peg::Rule Identifier;
  static peg::Rule IdentStart;
  static peg::Rule IdnetCont;
  static peg::Rule Literal;
  static peg::Rule Class;
  static peg::Rule Range;
  static peg::Rule Char;
  static peg::Rule LEFTARROW;
  static peg::Rule SLASH;
  static peg::Rule AND;
  static peg::Rule NOT;
  static peg::Rule QUESTION;
  static peg::Rule STAR;
  static peg::Rule PLUS;
  static peg::Rule OPEN;
  static peg::Rule CLOSE;
  static peg::Rule DOT;
  static peg::Rule Spacing;
  static peg::Rule Comment;
  static peg::Rule Space;
  static peg::Rule EndOfLine;
  static peg::Rule EndOfFile;
  static peg::Rule Action;
  static peg::Rule BEGIN;
  static peg::Rule END;
};

peg::Rule PegSample::Identifier = !peg::any;
peg::Rule PegSample::IdentStart = !peg::any;
peg::Rule PegSample::IdnetCont = !peg::any;
peg::Rule PegSample::Literal = !peg::any;
peg::Rule PegSample::Class = !peg::any;
peg::Rule PegSample::Range = !peg::any;
peg::Rule PegSample::Char =
  (peg::char_('\\') >> (peg::char_('a') / peg::char_('b') / peg::char_('e') / peg::char_('f')
			/ peg::char_('n') / peg::char_('r') / peg::char_('t') / peg::char_('v')
			/ peg::char_('\'') / peg::char_('"') / peg::char_('[') / peg::char_(']') / peg::char_('\\')))
  / (peg::char_('\\') >> peg::range('0', '3') >> peg::range('0', '7') >> peg::range('0', '7'))
  / (peg::char_('\\') >> peg::range('0', '7') >> peg::range('0', '7'))
  / peg::str("\\-")
  / ((!peg::char_('\\')) >> peg::any);
peg::Rule PegSample::LEFTARROW = peg::str("<-") >> Spacing;
peg::Rule PegSample::SLASH = peg::char_('/') >> Spacing;
peg::Rule PegSample::AND = peg::char_('&') >> Spacing;
peg::Rule PegSample::NOT = peg::char_('!') >> Spacing;
peg::Rule PegSample::QUESTION = peg::char_('?') >> Spacing;
peg::Rule PegSample::STAR = peg::char_('*') >> Spacing;
peg::Rule PegSample::PLUS = peg::char_('+') >> Spacing;
peg::Rule PegSample::OPEN = peg::char_('(') >> Spacing;
peg::Rule PegSample::CLOSE = peg::char_(')') >> Spacing;
peg::Rule PegSample::DOT = peg::char_('.') >> Spacing;
peg::Rule PegSample::Spacing = *(Space / Comment);
peg::Rule PegSample::Comment = peg::char_('#') >> *(!EndOfLine >> peg::any) >> EndOfLine;
peg::Rule PegSample::Space = peg::char_(' ') / peg::char_('\t') / EndOfLine;
peg::Rule PegSample::EndOfLine = peg::str("\r\n") / peg::char_('\n') / peg::char_('\r');
peg::Rule PegSample::EndOfFile = !peg::any;

peg::Rule PegSample::Action = peg::char_('{') >> *(!peg::char_('}') >> peg::any) >> peg::char_('}') >> Spacing;
peg::Rule PegSample::BEGIN = peg::char_('<') >> Spacing;
peg::Rule PegSample::END = peg::char_('>') >> Spacing;

TEST_F(PegSample, Identifier)
{
}

TEST_F(PegSample, IdentStart)
{
}

TEST_F(PegSample, IdnetCont)
{
}

TEST_F(PegSample, Literal)
{
}

TEST_F(PegSample, Class)
{
}

TEST_F(PegSample, Range)
{
}

TEST_F(PegSample, Char)
{
  peg::Result result = peg::parse(+Char, "\\a\\b\\e\\f\\n\\r\\t\\v\\\'\\\"\\[\\]\\\\");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);

  for (int i = 0; i <= 0377; ++i) {
    char buf[5];
    snprintf(buf, sizeof buf, "\\%03o", i);
    result = peg::parse(Char, buf);
    EXPECT_EQ(true, result.status);
    EXPECT_STREQ("", result.rest);
  }

  for (int i = 0; i <= 077; ++i) {
    char buf[4];
    snprintf(buf, sizeof buf, "\\%02o", i);
    result = peg::parse(Char, buf);
    EXPECT_EQ(true, result.status);
    EXPECT_STREQ("", result.rest);
  }

  result = peg::parse(Char, "\\-");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);

  for (int i = 1; i <= 0xff; ++i) {
    if (i == '\\') {
      continue;
    }
    char buf[2];
    snprintf(buf, sizeof buf, "%c", i);
    result = peg::parse(Char, buf);
    EXPECT_EQ(true, result.status);
    EXPECT_STREQ("", result.rest);
  }
}

TEST_F(PegSample, LEFTARROW)
{
  peg::Result result = peg::parse(LEFTARROW, "<- \t\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, SLASH)
{
  peg::Result result = peg::parse(SLASH, "/ \t\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, AND)
{
  peg::Result result = peg::parse(AND, "& \t\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, NOT)
{
  peg::Result result = peg::parse(NOT, "! \t\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, QUESTION)
{
  peg::Result result = peg::parse(QUESTION, "? \t\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, STAR)
{
  peg::Result result = peg::parse(STAR, "* \t\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, PLUS)
{
  peg::Result result = peg::parse(PLUS, "+ \t\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, OPEN)
{
  peg::Result result = peg::parse(OPEN, "( \t\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, CLOSE)
{
  peg::Result result = peg::parse(CLOSE, ") \t\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, DOT)
{
  peg::Result result = peg::parse(DOT, ". \t\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, Spacing)
{
  peg::Result result = peg::parse(Spacing, "# comment.\n\r\n\n# comment.\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, Comment)
{
  peg::Result result = peg::parse(Comment, "# comment.\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, Space)
{
  peg::Result result = peg::parse(Space, " ");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);

  result = peg::parse(Space, "\t");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);

  result = peg::parse(Space, "\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);

  result = peg::parse(Space, "\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);

  result = peg::parse(Space, "\r");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, EndOfLine)
{
  peg::Result result = peg::parse(EndOfLine, "\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);

  result = peg::parse(EndOfLine, "\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);

  result = peg::parse(EndOfLine, "\r");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, EndOfFile)
{
  peg::Result result = peg::parse(EndOfFile, "");
  EXPECT_EQ(true, result.status);
}

TEST_F(PegSample, Action)
{
  peg::Result result = peg::parse(Action, "{ printf(\"Hello.\n\"); }");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, BEGIN)
{
  peg::Result result = peg::parse(BEGIN, "< \t\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}

TEST_F(PegSample, END)
{
  peg::Result result = peg::parse(END, "> \t\r\n");
  EXPECT_EQ(true, result.status);
  EXPECT_STREQ("", result.rest);
}
