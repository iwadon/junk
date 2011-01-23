#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <iostream>
#include <string>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextTestProgressListener.h>
#ifdef HAVE_BOOST
#include <boost/foreach.hpp>
#endif
#ifdef HAVE_BOOST_PROGRAM_OPTIONS
#include <boost/program_options.hpp>
namespace po = boost::program_options;
#endif
#include "logger.hpp"

int main(int argc, char *argv[])
{
  po::options_description opt(std::string("Usage: ") + argv[0] + " [Options] [Test Path] ...\nOptions");
  opt.add_options()
    ("help,h", "Print this help")
    ("verbose,v", "Verbose mode")
    ("test-path,t", po::value<std::vector<std::string> >(), "Specify the test path");
  po::positional_options_description p;
  p.add("test-path", -1);
  po::variables_map vars;
  try {
    po::store(po::command_line_parser(argc, argv).options(opt).positional(p).run(), vars);
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
  if (vars.count("test-path") > 0) {
    CppUnit::TestResult controller;
    CppUnit::TestResultCollector result;
    controller.addListener(&result);
    CppUnit::TextTestProgressListener progress;
    controller.addListener(&progress);
    const std::vector<std::string> &v = vars["test-path"].as<std::vector<std::string> >();
    BOOST_FOREACH(std::string i, v) {
      std::cout << i << " ";
      try {
	runner.run(controller, i);
      } catch (std::invalid_argument &e) {
	std::cerr << "ERROR: " << e.what() << std::endl;
	return 1;
      }
    }
    CppUnit::TextOutputter outputter(&result, std::cerr);
    outputter.write();
    return result.wasSuccessful() ? 0 : 1;
  } else {
    return runner.run() ? 0 : 1;
  }
}
