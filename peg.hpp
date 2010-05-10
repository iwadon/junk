#ifndef PEG_HPP_INCLUDED
#define PEG_HPP_INCLUDED 1

#include <string>

namespace peg
{
  struct Result
  {
    bool status;
    const char *rest;
  };

  class ParsingExpression
  {
  public:
    virtual Result parse(const char *src) = 0;
    virtual std::string inspect() const = 0;
    template <typename F>
    ParsingExpression &operator[](F f);
    ParsingExpression &operator>>(ParsingExpression &rhs);
    ParsingExpression &operator/(ParsingExpression &rhs);
    ParsingExpression &operator*();
    ParsingExpression &operator+();
    ParsingExpression &operator-();
  };

  template <typename F>
  class Action : public ParsingExpression
  {
  public:
    Action(ParsingExpression *pe, F action);
    Result parse(const char *src);
    std::string inspect() const;
  private:
    ParsingExpression *pe_;
    F action_;
  };

  class Any : public ParsingExpression
  {
  public:
    Result parse(const char *src);
    std::string inspect() const;
  };

  class Byte : public ParsingExpression
  {
  public:
    Byte(const size_t bytes);
    Result parse(const char *src);
    std::string inspect() const;
  private:
    size_t bytes_;
  };

  class Char : public ParsingExpression
  {
  public:
    Char(const char chr);
    Result parse(const char *src);
    std::string inspect() const;
  private:
    char chr_;
  };

  class Sequence : public ParsingExpression
  {
  public:
    Sequence(ParsingExpression &lhs, ParsingExpression &rhs);
    Result parse(const char *src);
    std::string inspect() const;
  private:
    ParsingExpression &lhs_;
    ParsingExpression &rhs_;
  };

  class OrderedChoice : public ParsingExpression
  {
  public:
    OrderedChoice(ParsingExpression &lhs, ParsingExpression &rhs);
    Result parse(const char *src);
    std::string inspect() const;
  private:
    ParsingExpression &lhs_;
    ParsingExpression &rhs_;
  };

  class ZeroOrMore : public ParsingExpression
  {
  public:
    ZeroOrMore(ParsingExpression &pe);
    Result parse(const char *src);
    std::string inspect() const;
  private:
    ParsingExpression &pe_;
  };

  class OneOrMore : public ParsingExpression
  {
  public:
    OneOrMore(ParsingExpression &pe);
    Result parse(const char *src);
    std::string inspect() const;
  private:
    ParsingExpression &pe_;
  };

  class Optional : public ParsingExpression
  {
  public:
    Optional(ParsingExpression &pe);
    Result parse(const char *src);
    std::string inspect() const;
  private:
    ParsingExpression &pe_;
  };

  class Rule : public ParsingExpression
  {
  public:
    Rule();
    Rule(ParsingExpression &pe);
    Result parse(const char *src);
    std::string inspect() const;
  private:
    ParsingExpression *pe_;
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

  template <typename F>
  inline Action<F>::Action(ParsingExpression *pe, F f)
    : pe_(pe)
    , action_(f)
  {
  }

  template <typename F>
  inline Result Action<F>::parse(const char *str)
  {
    Result result = pe_->parse(str);
    action_(str, result.rest);
    return result;
  }

  template <typename F>
  inline std::string Action<F>::inspect() const
  {
    return pe_->inspect();
  }

  extern Any any;

  ParsingExpression &byte(const size_t bytes);
  ParsingExpression &char_(const char chr);
}

#endif // defined(PEG_HPP_INCLUDED)
