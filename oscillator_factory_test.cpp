#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator_factory.hpp"
#include <gtest/gtest.h>
#ifdef HAVE_BOOST
#include <boost/shared_ptr.hpp>
#endif
#include "oscillator.hpp"

TEST(OscillatorFactoryTest, create)
{
  OscillatorFactory of;
  boost::shared_ptr<Oscillator> o(of.create("sin"));
  ASSERT_TRUE(o != NULL);
  o = boost::shared_ptr<Oscillator>(of.create("unknown"));
  ASSERT_TRUE(o == NULL);
}
