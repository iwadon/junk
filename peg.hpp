#ifndef PEG_HPP_INCLUDED
#define PEG_HPP_INCLUDED 1

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
    template <typename F>
    ParsingExpression &operator[](F f);
    ParsingExpression &operator/(ParsingExpression &rhs);
  };

  template <typename F>
  class Action : public ParsingExpression
  {
  public:
    Action(ParsingExpression *pe, F action);
    Result parse(const char *src);
  private:
    ParsingExpression *pe_;
    F action_;
  };

  class Any : public ParsingExpression
  {
  public:
    Result parse(const char *src);
  };

  class Byte : public ParsingExpression
  {
  public:
    Byte(const size_t bytes);
    Result parse(const char *src);
  private:
    size_t bytes_;
  };

  class Char : public ParsingExpression
  {
  public:
    Char(const char chr);
    Result parse(const char *src);
  private:
    char chr_;
  };

  class OrderedChoice : public ParsingExpression
  {
  public:
    OrderedChoice(ParsingExpression &lhs, ParsingExpression &rhs);
    Result parse(const char *src);
  private:
    ParsingExpression &lhs_;
    ParsingExpression &rhs_;
  };

  class Rule : public ParsingExpression
  {
  public:
    Rule();
    Rule(ParsingExpression &pe);
    Result parse(const char *src);
  private:
    ParsingExpression *pe_;
  };

  template <typename F>
  inline ParsingExpression &ParsingExpression::operator[](F f)
  {
    ParsingExpression *pe = new Action<F>(this, f);
    return *pe;
  }

  inline ParsingExpression &ParsingExpression::operator/(ParsingExpression &rhs)
  {
    ParsingExpression *pe = new OrderedChoice(*this, rhs);
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

  extern Any any;

  ParsingExpression &byte(const size_t bytes);
  ParsingExpression &char_(const char chr);
}

#endif // defined(PEG_HPP_INCLUDED)
