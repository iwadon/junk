#ifndef PEG_HPP_INCLUDED
#define PEG_HPP_INCLUDED 1

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "logger.hpp"

namespace peg
{
  class ErrorInfo;

  struct Result
  {
    bool status;
    const char *rest;
    std::string inspect() const;
  };

  class ParsingExpression
  {
  public:
    virtual Result parse(ErrorInfo &err, const char *src) = 0;
    virtual std::string str() const = 0;
    virtual std::string inspect() const = 0;
    virtual bool is_operator() const = 0;
    template <typename F>
    ParsingExpression &operator[](F f);
    ParsingExpression &operator>>(ParsingExpression &rhs);
    ParsingExpression &operator/(ParsingExpression &rhs);
    ParsingExpression &operator*();
    ParsingExpression &operator+();
    ParsingExpression &operator-();
    ParsingExpression &operator&();
    ParsingExpression &operator!();
  };

  class ErrorInfo
  {
  public:
    typedef std::pair<std::string, peg::Result> info_type;
    void clear();
    bool empty() const;
    std::string message() const;
    void push(std::string &src, const peg::Result &result);
    size_t size() const;
    info_type operator[](const size_t index) const;
    void update(const ParsingExpression &pe, const Result &result);
  private:
    typedef std::vector<info_type> info_list_type;
    info_list_type info_list_;
  };

  template <typename F>
  class Action : public ParsingExpression
  {
  public:
    Action(ParsingExpression *pe, F action);
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return false; }
  private:
    ParsingExpression *pe_;
    F action_;
    mutable bool in_inspect_;
  };

  class Any : public ParsingExpression
  {
  public:
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return false; }
  };

  class Byte : public ParsingExpression
  {
  public:
    Byte(const size_t bytes);
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return false; }
  private:
    size_t bytes_;
  };

  class Char : public ParsingExpression
  {
  public:
    Char(const char chr);
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return false; }
  private:
    char chr_;
  };

  class String : public ParsingExpression
  {
  public:
    String(const char *str);
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return false; }
  private:
    std::string str_;
  };

  class Range : public ParsingExpression
  {
  public:
    Range(const char first, const char last);
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return false; }
  private:
    char first_;
    char last_;
  };

  class Sequence : public ParsingExpression
  {
  public:
    Sequence(ParsingExpression &lhs, ParsingExpression &rhs);
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return true; }
  private:
    ParsingExpression &lhs_;
    ParsingExpression &rhs_;
  };

  class OrderedChoice : public ParsingExpression
  {
  public:
    OrderedChoice(ParsingExpression &lhs, ParsingExpression &rhs);
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return true; }
  private:
    ParsingExpression &lhs_;
    ParsingExpression &rhs_;
  };

  class ZeroOrMore : public ParsingExpression
  {
  public:
    ZeroOrMore(ParsingExpression &pe);
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return true; }
  private:
    ParsingExpression &pe_;
  };

  class OneOrMore : public ParsingExpression
  {
  public:
    OneOrMore(ParsingExpression &pe);
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return true; }
  private:
    ParsingExpression &pe_;
  };

  class Optional : public ParsingExpression
  {
  public:
    Optional(ParsingExpression &pe);
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return true; }
  private:
    ParsingExpression &pe_;
  };

  class AndPredicate : public ParsingExpression
  {
  public:
    AndPredicate(ParsingExpression &pe);
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return true; }
  private:
    ParsingExpression &pe_;
  };

  class NotPredicate : public ParsingExpression
  {
  public:
    NotPredicate(ParsingExpression &pe);
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return true; }
  private:
    ParsingExpression &pe_;
  };

  class Rule : public ParsingExpression
  {
  public:
    Rule();
    Rule(ParsingExpression &pe);
    Result parse(ErrorInfo &err, const char *src);
    std::string str() const;
    std::string inspect() const;
    bool is_operator() const { return pe_->is_operator(); }
  private:
    ParsingExpression *pe_;
    mutable bool in_str_;
    mutable bool in_inspect_;
  };

  template <typename F>
  inline ParsingExpression &ParsingExpression::operator[](F f)
  {
    ParsingExpression *pe = new Action<F>(this, f);
    return *pe;
  }

  inline ParsingExpression &ParsingExpression::operator>>(ParsingExpression &rhs)
  {
    ParsingExpression *pe = new Sequence(*this, rhs);
    return *pe;
  }

  inline ParsingExpression &ParsingExpression::operator/(ParsingExpression &rhs)
  {
    ParsingExpression *pe = new OrderedChoice(*this, rhs);
    return *pe;
  }

  inline ParsingExpression &ParsingExpression::operator*()
  {
    ParsingExpression *pe = new ZeroOrMore(*this);
    return *pe;
  }

  inline ParsingExpression &ParsingExpression::operator+()
  {
    ParsingExpression *pe = new OneOrMore(*this);
    return *pe;
  }

  inline ParsingExpression &ParsingExpression::operator-()
  {
    ParsingExpression *pe = new Optional(*this);
    return *pe;
  }

  inline ParsingExpression &ParsingExpression::operator&()
  {
    ParsingExpression *pe = new AndPredicate(*this);
    return *pe;
  }

  inline ParsingExpression &ParsingExpression::operator!()
  {
    ParsingExpression *pe = new NotPredicate(*this);
    return *pe;
  }

  template <typename F>
  inline Action<F>::Action(ParsingExpression *pe, F f)
    : pe_(pe)
    , action_(f)
    , in_inspect_(false)
  {
  }

  template <typename F>
  inline Result Action<F>::parse(ErrorInfo &err, const char *str)
  {
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    Result result = pe_->parse(err, str);
    if (result.status) {
      //std::cout << "OK" << std::endl;
      action_(str, result.rest);
    } else {
      //std::cout << "NG" << std::endl;
    }
    return result;
  }

  template <typename F>
  inline std::string Action<F>::str() const
  {
    return pe_->str();
  }

  template <typename F>
  inline std::string Action<F>::inspect() const
  {
    if (in_inspect_) {
      return "[...]";
    } else {
      in_inspect_ = true;
      std::string str(pe_->inspect());
      in_inspect_ = false;
      return str;
    }
  }

  inline Result parse(ParsingExpression &pe, const char *src)
  {
    ErrorInfo err;
    Result result = pe.parse(err, src);
    if (!result.status) {
      LOG_ERROR(err.message().c_str());
    }
    return result;
  }

  extern Any any;

  ParsingExpression &byte(const size_t bytes);
  ParsingExpression &char_(const char chr);
  ParsingExpression &str(const char *str);
  ParsingExpression &range(const char first, const char last);

  const char *encode_char(const char ch);
  std::string encode_str(const char *str, const size_t len, const size_t limit = 0);
}

#endif // defined(PEG_HPP_INCLUDED)
