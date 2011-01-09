#ifndef OSCILLATOR_FACTORY_HPP_INCLUDED
#define OSCILLATOR_FACTORY_HPP_INCLUDED 1

#include <map>
#include "sp.hpp"

class Oscillator;

class OscillatorFactory
{
public:
  OscillatorFactory();
  Oscillator *create(const SP &name);
private:
  typedef Oscillator *(*factory_type)();
  std::map<std::string, factory_type> factories_;
};

#endif // !defined(OSCILLATOR_FACTORY_HPP_INCLUDED)
