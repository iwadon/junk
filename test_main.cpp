#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include "logger.hpp"

int main()
{
  Logger::get_instance().set_level(Logger::LEVEL_FATAL);
  CppUnit::TextTestRunner runner;
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  return runner.run() ? 0 : 1;
}
