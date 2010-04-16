#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

int main()
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  return runner.run() ? 0 : 1;
}
