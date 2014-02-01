#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_BOOST_PROGRAM_OPTIONS
#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <iostream>
#endif

int main(int argc, char *argv[])
{
#ifdef HAVE_BOOST_PROGRAM_OPTIONS
  po::options_description od;
  od.add_options()
    ("help,h", "Print this help");
  po::variables_map vars;
  try {
    po::store(po::command_line_parser(argc, argv).options(od).run(), vars);
    po::notify(vars);
    if (vars.count("help") != 0) {
      std::cerr << od << std::endl;
      return 1;
    }
  } catch (std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    std::cerr << od << std::endl;
    return 1;
  }
#endif // defined(HAVE_BOOST_PROGRAM_OPTIONS)
  return 0;
}
