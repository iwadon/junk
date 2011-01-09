#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator_factory.hpp"
#include "oscillator.hpp"

static Oscillator *create_sin()
{
  return new Oscillator;
}

OscillatorFactory::OscillatorFactory()
{
  factories_["sin"] = create_sin;
}

Oscillator *OscillatorFactory::create(const SP &name)
{
  std::string key;
  name.CopyToString(&key);
  if (factories_.count(key) > 0) {
    factory_type factory = factories_[key];
    Oscillator *osc = factory();
    return osc;
  } else {
    return NULL;
  }
}
