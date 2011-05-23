#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "logger.hpp"
#include <gtest/gtest.h>
#include <sstream>

#define DEFUN_TEST_FUNC(name, output1, output2, output3, output4, output5, func, ...) \
  TEST(LoggerTest, name)						\
  {									\
    {									\
      std::ostringstream oss;						\
      Logger logger(oss, Logger::LEVEL_DEBUG);				\
      logger.func(__VA_ARGS__);						\
      EXPECT_EQ(std::string(output1), oss.str());			\
    }									\
    {									\
      std::ostringstream oss;						\
      Logger logger(oss, Logger::LEVEL_INFO);				\
      logger.func(__VA_ARGS__);						\
      EXPECT_EQ(std::string(output2), oss.str());			\
    }									\
    {									\
      std::ostringstream oss;						\
      Logger logger(oss, Logger::LEVEL_WARN);				\
      logger.func(__VA_ARGS__);						\
      EXPECT_EQ(std::string(output3), oss.str());			\
    }									\
    {									\
      std::ostringstream oss;						\
      Logger logger(oss, Logger::LEVEL_ERROR);				\
      logger.func(__VA_ARGS__);						\
      EXPECT_EQ(std::string(output4), oss.str());			\
    }									\
    {									\
      std::ostringstream oss;						\
      Logger logger(oss, Logger::LEVEL_FATAL);				\
      logger.func(__VA_ARGS__);						\
      EXPECT_EQ(std::string(output5), oss.str());			\
    }									\
  }
DEFUN_TEST_FUNC(debug, "DEBUG: Hello.\n", "", "", "", "", debug, "Hello.");
DEFUN_TEST_FUNC(info, "INFO: Hello.\n", "INFO: Hello.\n", "", "", "", info, "Hello.");
DEFUN_TEST_FUNC(warn, "WARN: Hello.\n", "WARN: Hello.\n", "WARN: Hello.\n", "", "", warn, "Hello.");
DEFUN_TEST_FUNC(error, "ERROR: Hello.\n", "ERROR: Hello.\n", "ERROR: Hello.\n", "ERROR: Hello.\n", "", error, "Hello.");
DEFUN_TEST_FUNC(fatal, "FATAL: Hello.\n", "FATAL: Hello.\n", "FATAL: Hello.\n", "FATAL: Hello.\n", "FATAL: Hello.\n", fatal, "Hello.");
DEFUN_TEST_FUNC(log_debug, "DEBUG: Hello.\n", "", "", "", "", log, Logger::LEVEL_DEBUG, "Hello.");
DEFUN_TEST_FUNC(log_info, "INFO: Hello.\n", "INFO: Hello.\n", "", "", "", log, Logger::LEVEL_INFO, "Hello.");
DEFUN_TEST_FUNC(log_warn, "WARN: Hello.\n", "WARN: Hello.\n", "WARN: Hello.\n", "", "", log, Logger::LEVEL_WARN, "Hello.");
DEFUN_TEST_FUNC(log_error, "ERROR: Hello.\n", "ERROR: Hello.\n", "ERROR: Hello.\n", "ERROR: Hello.\n", "", log, Logger::LEVEL_ERROR, "Hello.");
DEFUN_TEST_FUNC(log_fatal, "FATAL: Hello.\n", "FATAL: Hello.\n", "FATAL: Hello.\n", "FATAL: Hello.\n", "FATAL: Hello.\n", log, Logger::LEVEL_FATAL, "Hello.");

TEST(LoggerTest, set_level)
{
  std::stringstream oss;
  Logger logger(oss, Logger::LEVEL_DEBUG);
  logger.debug("Hello.");
  EXPECT_EQ(std::string("DEBUG: Hello.\n"), oss.str());
  oss.str("");
  logger.set_level(Logger::LEVEL_INFO);
  logger.debug("Hello.");
  EXPECT_EQ(std::string(""), oss.str());
  oss.str("");
  logger.set_level(Logger::LEVEL_DEBUG);
  logger.debug("Hello.");
  EXPECT_EQ(std::string("DEBUG: Hello.\n"), oss.str());
}
