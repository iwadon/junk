#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cstring>
#include "peg.hpp"

namespace peg
{
  Any any;

  Result Any::parse(const char *str)
  {
    Result result = {true, str + 1};
    return result;
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
