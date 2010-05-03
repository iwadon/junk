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

  template <typename F>
  inline ParsingExpression &ParsingExpression::operator[](F f)
  {
    ParsingExpression *pe = new Action<F>(this, f);
    return *pe;
  }

  template <typename F>
  inline Action<F>::Action(ParsingExpression *pe, F f)
    : pe_(pe)
    , action_(f)
  {
  }

  template <typename F>
  Result Action<F>::parse(const char *str)
  {
    Result result = pe_->parse(str);
    action_(str, result.rest);
    return result;
  }

  extern Any any;
}

#endif // defined(PEG_HPP_INCLUDED)
