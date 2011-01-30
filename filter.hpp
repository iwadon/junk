#ifndef FILTER_HPP_INCLUDED
#define FILTER_HPP_INCLUDED 1

class Filter
{
public:
  virtual ~Filter() {}
  virtual float value(const float input) = 0;
};

#endif // !defined(FILTER_HPP_INCLUDED)
