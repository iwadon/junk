#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator_factory.hpp"
#include "sine_wave_oscillator.hpp"
#include "triangle_wave_oscillator.hpp"
#include "pseudo_triangle_wave_oscillator.hpp"

OscillatorFactory &OscillatorFactory::get_instance()
{
  static OscillatorFactory instance;
  return instance;
}

static Oscillator *create_sin()
{
  return new SineWaveOscillator;
}

static Oscillator *create_tri()
{
  return new TriangleWaveOscillator;
}

static Oscillator *create_ptri()
{
  return new PseudoTriangleWaveOscillator;
}

OscillatorFactory::OscillatorFactory()
{
  factories_["sin"] = create_sin;
  factories_["tri"] = create_tri;
  factories_["ptri"] = create_ptri;
}

Oscillator *OscillatorFactory::create(const SP &name)
{
  std::string key;
  name.CopyToString(&key);
  if (factories_.count(key) > 0) {
    factory_type factory = factories_[key];
    return factory();
  } else {
    return NULL;
  }
}
