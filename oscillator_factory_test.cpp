#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator_factory.hpp"
#include "oscillator.hpp"
#include <gtest/gtest.h>
#include <memory>

TEST(OscillatorFactoryTest, create)
{
  OscillatorFactory of;
  std::shared_ptr<Oscillator> o(of.create("sin"));
  ASSERT_TRUE(o != NULL);
  o = std::shared_ptr<Oscillator>(of.create("unknown"));
  ASSERT_TRUE(o == NULL);
}
