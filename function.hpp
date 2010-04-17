#ifndef FUNCTION_HPP_INCLUDED
#define FUNCTION_HPP_INCLUDED

template <typename> class Function;

template <typename R>
class Function<R()>
{
public:
  typedef R (*function_type)();

  Function(function_type func)
    : func_(func)
  {
  }
  R operator()()
  {
    return func_();
  }
private:
  function_type func_;
};

template <typename R, typename A1>
class Function<R(A1)>
{
public:
  typedef R (*function_type)(A1);

  Function(function_type func)
    : func_(func)
  {
  }
  R operator()(A1 a1)
  {
    return func_(a1);
  }
private:
  function_type func_;
};

template <typename R, typename A1, typename A2>
class Function<R(A1, A2)>
{
public:
  typedef R (*function_type)(A1, A2);

  Function(function_type func)
    : func_(func)
  {
  }
  R operator()(A1 a1, A2 a2)
  {
    return func_(a1, a2);
  }
private:
  function_type func_;
};

template <typename R, typename A1, typename A2, typename A3>
class Function<R(A1, A2, A3)>
{
public:
  typedef R (*function_type)(A1, A2, A3);

  Function(function_type func)
    : func_(func)
  {
  }
  R operator()(A1 a1, A2 a2, A3 a3)
  {
    return func_(a1, a2, a3);
  }
private:
  function_type func_;
};

#endif // !defined(FUNCTION_HPP_INCLUDED)
