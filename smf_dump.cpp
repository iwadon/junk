#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <iostream>
#include "logger.hpp"
#include "smf.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " FILE" << std::endl;
    return 1;
  }
  SMF smf;
  if (!smf.load_file(argv[1])) {
    ERROR("Failed to load file: %s", argv[1]);
    return 1;
  }
  smf.play();
  while (smf.is_playing()) {
    smf.update();
  }
  return 0;
}
