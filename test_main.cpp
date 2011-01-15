#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <iostream>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#ifdef HAVE_BOOST_PROGRAM_OPTIONS
#include <boost/program_options.hpp>
namespace po = boost::program_options;
#endif
#include "logger.hpp"

int main(int argc, char *argv[])
{
  po::options_description opt(std::string("Usage: ") + argv[0] + " [Options]\nOptions");
  opt.add_options()
    ("help,h", "Print this help")
    ("verbose,v", "Verbose mode");
  po::variables_map vars;
  try {
    po::store(po::parse_command_line(argc, argv, opt), vars);
    po::notify(vars);
    if (vars.count("help") != 0) {
      std::cerr << opt << std::endl;
      return 1;
    }
    if (vars.count("verbose") == 0) {
      Logger::get_instance().set_level(Logger::LEVEL_FATAL);
    }
  } catch (std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    std::cerr << opt << std::endl;
    return 1;
  }
  CppUnit::TextTestRunner runner;
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  return runner.run() ? 0 : 1;
}
