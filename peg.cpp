#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "peg.hpp"
#ifdef STDCXX_98_HEADERS
#include <cctype>
#include <cstring>
#include <iostream>
#endif
#ifdef HAVE_BOOST
#include <boost/format.hpp>
#include <boost/utility.hpp>
#endif

namespace peg
{
  const char *encode_char(const char ch)
  {
    static char buf[4 + 1];
    char *p = buf;
    if (isgraph(ch)) {
      *p++ = ch;
    } else {
      *p++ = '\\';
      switch (ch) {
      case '\n':
	*p++ = 'n';
	break;
      case '\r':
	*p++ = 'r';
	break;
      case '\t':
	*p++ = 't';
	break;
      default:
	snprintf(p, sizeof buf - 1, "x%02X", static_cast<unsigned char>(ch));
	p += 3;
	break;
      }
    }
    *p = '\0';
    return buf;
  }

  std::string encode_str(const char *str, const size_t len, const size_t limit)
  {
    std::string s;
    //size_t len = strlen(str);
    size_t len_ = len;
    if (len_ == 0) {
      len_ = strlen(str);
    }
    size_t l;
    if (limit > 0) {
      l = std::min(len_, static_cast<size_t>(limit));
    } else {
      l = len_;
    }
    size_t i;
    for (i = 0; i < l; ++i) {
      char c = str[i];
      if (c == '\0') {
	break;
      }
      s += encode_char(c);
    }
    if (i == l && len > l) {
      s += "...";
    }
    return s;
  }

  std::string Result::inspect() const
  {
    std::string s("#<peg::Result ");
    s += status ? "OK" : "NG";
    s += " \"";
    s += encode_str(rest, 10);
    s += "\">";
    return s;
  }

  void ErrorInfo::clear()
  {
    info_list_.clear();
  }

  bool ErrorInfo::empty() const
  {
    return info_list_.empty();
  }

  std::string ErrorInfo::message() const
  {
    const info_type &info = info_list_[0];
    std::string s = "parse error: expect ";
    s += info.first;
    s += ", but \"";
    s += encode_str(info.second.rest, 8);
    s += "\"";
    return s;
  }

  void ErrorInfo::push(std::string &msg, const Result &result)
  {
    info_type info(msg, result);
    info_list_.push_back(info);
  }

  size_t ErrorInfo::size() const
  {
    return info_list_.size();
  }

  ErrorInfo::info_type ErrorInfo::operator[](const size_t index) const
  {
    return info_list_[index];
  }

  void ErrorInfo::update(const ParsingExpression &pe, const Result &result)
  {
    if (result.status) {
      clear();
    } else {
      std::string msg = pe.str();
      push(msg, result);
    }
  }

  Result Any::parse(ErrorInfo &err, const char *src)
  {
    Result result;
    if (*src != '\0') {
      result.status = true;
      result.rest = src + 1;
    } else {
      result.status = false;
      result.rest = src + 0;
    }
    err.update(*this, result);
    return result;
  }

  std::string Any::str() const
  {
    std::string str(".");
    return str;
  }

  std::string Any::inspect() const
  {
    std::string str("#<peg::Any>");
    return str;
  }

  Byte::Byte(const size_t bytes)
    : bytes_(bytes)
  {
  }

  Result Byte::parse(ErrorInfo &err, const char *src)
  {
    Result result = {true, src + bytes_};
    err.update(*this, result);
    return result;
  }

  std::string Byte::str() const
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

  std::string Byte::inspect() const
  {
    std::string str("#<peg::Any>");
    return str;
  }

  Char::Char(const char chr)
    : chr_(chr)
  {
  }

  Result Char::parse(ErrorInfo &err, const char *src)
  {
    Result result;
    if (*src == chr_) {
      result.status = true;
      result.rest = src + 1;
    } else {
      result.status = false;
      result.rest = src;
    }
    err.update(*this, result);
    return result;
  }

  std::string Char::str() const
  {
    std::string str = "'";
    str += encode_char(chr_);
    str += "'";
    return str;
  }

  std::string Char::inspect() const
  {
    std::string str("#<peg::Char '");
    str += encode_char(chr_);
    str += "'>";
    return str;
  }

  String::String(const char *str)
    : str_(str)
  {
  }

  Result String::parse(ErrorInfo &err, const char *src)
  {
    Result result;
    if (!strncmp(src, str_.c_str(), str_.size())) {
      result.status = true;
      result.rest = src + str_.size();
    } else {
      result.status = false;
      result.rest = src;
    }
    err.update(*this, result);
    return result;
  }

  std::string String::str() const
  {
    std::string str = "\"";
    str += encode_str(str_.c_str(), 0);
    str += "\"";
    return str;
  }

  std::string String::inspect() const
  {
    std::string str("#<peg::String \"");
    str += encode_str(str_.c_str(), 0);
    str += "\">";
    return str;
  }

  Range::Range(const char first, const char last)
    : first_(first)
    , last_(last)
  {
  }

  Result Range::parse(ErrorInfo &err, const char *src)
  {
    Result result;
    if (*src >= first_ && *src <= last_) {
      result.status = true;
      result.rest = src + 1;
    } else {
      result.status = false;
      result.rest = src;
    }
    err.update(*this, result);
    return result;
  }

  std::string Range::str() const
  {
    std::string str = "[";
    str += first_;
    str += "-";
    str += last_;
    str += "]";
    return str;
  }

  std::string Range::inspect() const
  {
    std::string str("#<peg::Range '");
    str += encode_char(first_);
    str += "'..'";
    str += encode_char(last_);
    str += "'>";
    return str;
  }

  Sequence::Sequence(ParsingExpression &lhs, ParsingExpression &rhs)
    : lhs_(lhs)
    , rhs_(rhs)
  {
  }

  Result Sequence::parse(ErrorInfo &err, const char *src)
  {
    Result result = lhs_.parse(err, src);
    if (result.status) {
      result = rhs_.parse(err, result.rest);
    }
    if (!result.status) {
      result.rest = src;
    }
    err.update(*this, result);
    return result;
  }

  std::string Sequence::str() const
  {
    std::string str = lhs_.str();
    str += " ";
    str += rhs_.str();
    return str;
  }

  std::string Sequence::inspect() const
  {
    std::string str("#<peg::Sequence ");
    str += lhs_.inspect();
    str += ", ";
    str += rhs_.inspect();
    str += ">";
    return str;
  }

  OrderedChoice::OrderedChoice(ParsingExpression &lhs, ParsingExpression &rhs)
    : lhs_(lhs)
    , rhs_(rhs)
  {
  }

  Result OrderedChoice::parse(ErrorInfo &err, const char *src)
  {
    Result result = lhs_.parse(err, src);
    if (!result.status) {
      result = rhs_.parse(err, src);
    }
    err.update(*this, result);
    return result;
  }

  std::string OrderedChoice::str() const
  {
    std::string str = lhs_.str();
    str += " / ";
    str += rhs_.str();
    return str;
  }

  std::string OrderedChoice::inspect() const
  {
    std::string str("#<peg::OrderedChoice ");
    str += lhs_.inspect();
    str += ", ";
    str += rhs_.inspect();
    str += ">";
    return str;
  }

  ZeroOrMore::ZeroOrMore(ParsingExpression &pe)
    : pe_(pe)
  {
  }

  Result ZeroOrMore::parse(ErrorInfo &err, const char *src)
  {
    Result result = pe_.parse(err, src);
    while (*result.rest != '\0' && result.status) {
      result = pe_.parse(err, result.rest);
    }
    result.status = true;
    err.update(*this, result);
    return result;
  }

  std::string ZeroOrMore::str() const
  {
    std::string str("");
    if (pe_.is_operator()) {
      str += "(";
    }
    str += pe_.str();
    if (pe_.is_operator()) {
      str += ")";
    }
    str += "*";
    return str;
  }

  std::string ZeroOrMore::inspect() const
  {
    std::string str("#<peg::ZeroOrMore ");
    str += pe_.inspect();
    str += ">";
    return str;
  }

  OneOrMore::OneOrMore(ParsingExpression &pe)
    : pe_(pe)
  {
  }

  Result OneOrMore::parse(ErrorInfo &err, const char *src)
  {
    Result result = pe_.parse(err, src);
    if (!result.status) {
      err.update(*this, result);
      return result;
    }
    do {
      result = pe_.parse(err, result.rest);
    } while (*result.rest != '\0' && result.status);
    result.status = true;
    err.update(*this, result);
    return result;
  }

  std::string OneOrMore::str() const
  {
    std::string str("");
    if (pe_.is_operator()) {
      str += "(";
    }
    str += pe_.str();
    if (pe_.is_operator()) {
      str += ")";
    }
    str += "+";
    return str;
  }

  std::string OneOrMore::inspect() const
  {
    std::string str("#<peg::OneOrMore ");
    str += pe_.inspect();
    str += ">";
    return str;
  }

  Optional::Optional(ParsingExpression &pe)
    : pe_(pe)
  {
  }

  Result Optional::parse(ErrorInfo &err, const char *src)
  {
    Result result = pe_.parse(err, src);
    if (!result.status) {
      result.status = true;
      result.rest = src;
    }
    err.update(*this, result);
    return result;
  }

  std::string Optional::str() const
  {
    std::string str = pe_.str();
    str += "?";
    return str;
  }

  std::string Optional::inspect() const
  {
    std::string str("#<peg::Optional ");
    str += pe_.inspect();
    str += ">";
    return str;
  }

  AndPredicate::AndPredicate(ParsingExpression &pe)
    : pe_(pe)
  {
  }

  Result AndPredicate::parse(ErrorInfo &err, const char *src)
  {
    Result result = pe_.parse(err, src);
    result.rest = src;
    err.update(*this, result);
    return result;
  }

  std::string AndPredicate::str() const
  {
    std::string str = "&";
    str += pe_.str();
    return str;
  }

  std::string AndPredicate::inspect() const
  {
    std::string str("#<peg::AndPredicate ");
    str += pe_.inspect();
    str += ">";
    return str;
  }

  NotPredicate::NotPredicate(ParsingExpression &pe)
    : pe_(pe)
  {
  }

  Result NotPredicate::parse(ErrorInfo &err, const char *src)
  {
    Result result = pe_.parse(err, src);
    result.status = !result.status;
    result.rest = src;
    err.update(*this, result);
    return result;
  }

  std::string NotPredicate::str() const
  {
    std::string str = "!";
    str += pe_.str();
    return str;
  }

  std::string NotPredicate::inspect() const
  {
    std::string str("#<peg::NotPredicate ");
    str += pe_.inspect();
    str += ">";
    return str;
  }

  Rule::Rule()
    : pe_(NULL)
    , in_str_(false)
    , in_inspect_(false)
  {
  }

  Rule::Rule(ParsingExpression &pe)
    : pe_(boost::addressof(pe))
    , in_str_(false)
    , in_inspect_(false)
  {
  }

  Result Rule::parse(ErrorInfo &err, const char *src)
  {
    Result result = pe_->parse(err, src);
    err.update(*this, result);
    return result;
  }

  std::string Rule::str() const
  {
    if (in_str_) {
      return "[...]";
    } else {
      in_str_ = true;
      std::string s(pe_->str());
      in_str_ = false;
      return s;
    }
  }

  std::string Rule::inspect() const
  {
    std::string str("#<peg::Rule ");
    if (in_inspect_) {
      str += "[...]";
    } else {
      in_inspect_ = true;
      str += pe_->inspect();
      in_inspect_ = false;
    }
    str += ">";
    return str;
  }

  Any any;

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

  ParsingExpression &str(const char *str)
  {
    ParsingExpression *pe = new String(str);
    return *pe;
  }

  ParsingExpression &range(const char first, const char last)
  {
    ParsingExpression *pe = new Range(first, last);
    return *pe;
  }
}
