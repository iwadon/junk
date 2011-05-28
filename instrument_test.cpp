#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "instrument.hpp"
#include <gtest/gtest.h>
#include "patch.hpp"

TEST(InstrumentTest, set_patch)
{
  Instrument inst;
  Patch patch;
  EXPECT_EQ(true, inst.set_patch(0, &patch));
  EXPECT_EQ(false, inst.set_patch(0, &patch));
}
