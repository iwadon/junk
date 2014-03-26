#ifndef OSCILLATOR_FACTORY_HPP_INCLUDED
#define OSCILLATOR_FACTORY_HPP_INCLUDED 1

#include "noncopyable.hpp"
#include "sp.hpp"
#include <map>

class Oscillator;

class OscillatorFactory : public NonCopyable
{
public:
  static OscillatorFactory &get_instance();
  OscillatorFactory();
  Oscillator *create(const SP &name);
private:
  typedef Oscillator *(*factory_type)();
  std::map<std::string, factory_type> factories_;
};

#endif // !defined(OSCILLATOR_FACTORY_HPP_INCLUDED)
