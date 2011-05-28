#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "patch.hpp"
#include <gtest/gtest.h>
#include "sine_wave_oscillator.hpp"

TEST(PatchTest, CTOR)
{
  Patch patch;
  ASSERT_TRUE(patch.oscillator() == NULL);
}

TEST(PatchTest, set_oscillator)
{
  Patch patch;
  SineWaveOscillator osc;
  patch.set_oscillator(&osc);
  ASSERT_TRUE(patch.oscillator() == &osc);
}
