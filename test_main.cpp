#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include "logger.hpp"

int main()
{
  Logger::get_instance().set_level(Logger::LEVEL_FATAL);
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  return runner.run() ? 0 : 1;
}
