#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "patch.hpp"
#ifdef STDCXX_98_HEADERS
#include <cstddef>
#endif
#include "oscillator.hpp"

Patch::Patch()
  : oscillator_(NULL)
{
}

void Patch::set_oscillator(Oscillator *oscillator)
{
  oscillator_ = oscillator;
}
