#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef HAVE_BOOST
#include <boost/format.hpp>
#endif
#include "peg.hpp"

namespace peg
{
  Any any;

  Result Any::parse(const char *str)
  {
    Result result = {true, str + 1};
    return result;
  }

  std::string Any::inspect() const
  {
    std::string str(".");
    return str;
  }

  Byte::Byte(const size_t bytes)
    : bytes_(bytes)
  {
  }

  Result Byte::parse(const char *str)
  {
    Result result = {true, str + bytes_};
    return result;
  }

  std::string Byte::inspect() const
  {
    std::string str;
    switch (bytes_) {
    case 1:
      str = "[1 byte]";
      break;
    default:
      str = (boost::format("[%uB]") % bytes_).str();
      break;
    }
    return str;
  }

  Char::Char(const char chr)
    : chr_(chr)
  {
  }

  Result Char::parse(const char *str)
  {
    Result result;
    if (*str == chr_) {
      result.status = true;
      result.rest = str + 1;
    } else {
      result.status = false;
      result.rest = str;
    }
    return result;
  }

  std::string Char::inspect() const
  {
    std::string str = "'";
    str += chr_;
    str += "'";
    return str;
  }

  Sequence::Sequence(ParsingExpression &lhs, ParsingExpression &rhs)
    : lhs_(lhs)
    , rhs_(rhs)
  {
  }

  Result Sequence::parse(const char *src)
  {
    Result result = lhs_.parse(src);
    if (result.status) {
      result = rhs_.parse(result.rest);
      if (result.status) {
	return result;
      }
    }
    result.status = false;
    result.rest = src;
    return result;
  }

  std::string Sequence::inspect() const
  {
    std::string str = lhs_.inspect();
    str += " ";
    str += rhs_.inspect();
    return str;
  }

  OrderedChoice::OrderedChoice(ParsingExpression &lhs, ParsingExpression &rhs)
    : lhs_(lhs)
    , rhs_(rhs)
  {
  }

  Result OrderedChoice::parse(const char *src)
  {
    Result result = lhs_.parse(src);
    if (!result.status) {
      result = rhs_.parse(src);
    }
    return result;
  }

  std::string OrderedChoice::inspect() const
  {
    std::string str = lhs_.inspect();
    str += " / ";
    str += rhs_.inspect();
    return str;
  }

  ZeroOrMore::ZeroOrMore(ParsingExpression &pe)
    : pe_(pe)
  {
  }

  Result ZeroOrMore::parse(const char *src)
  {
    Result result = pe_.parse(src);
    while (result.status) {
      result = pe_.parse(result.rest);
    }
    result.status = true;
    return result;
  }

  std::string ZeroOrMore::inspect() const
  {
    std::string str = pe_.inspect();
    str += "*";
    return str;
  }

  OneOrMore::OneOrMore(ParsingExpression &pe)
    : pe_(pe)
  {
  }

  Result OneOrMore::parse(const char *src)
  {
    Result result = pe_.parse(src);
    if (!result.status) {
      return result;
    }
    while (result.status) {
      result = pe_.parse(result.rest);
    }
    result.status = true;
    return result;
  }

  std::string OneOrMore::inspect() const
  {
    std::string str = pe_.inspect();
    str += "+";
    return str;
  }

  Optional::Optional(ParsingExpression &pe)
    : pe_(pe)
  {
  }

  Result Optional::parse(const char *src)
  {
    Result result = pe_.parse(src);
    result.status = true;
    return result;
  }

  std::string Optional::inspect() const
  {
    std::string str = pe_.inspect();
    str += "?";
    return str;
  }

  Rule::Rule()
    : pe_(NULL)
  {
  }

  Rule::Rule(ParsingExpression &pe)
    : pe_(&pe)
  {
  }

  Result Rule::parse(const char *str)
  {
    if (pe_ != NULL) {
      return pe_->parse(str);
    } else {
      Result result = {false, str};
      return result;
    }
  }

  std::string Rule::inspect() const
  {
    return pe_->inspect();
  }

  ParsingExpression &byte(const size_t bytes)
  {
    ParsingExpression *pe = new Byte(bytes);
    return *pe;
  }

  ParsingExpression &char_(const char chr)
  {
    ParsingExpression *pe = new Char(chr);
    return *pe;
  }
}
