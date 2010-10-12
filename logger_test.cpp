#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "logger.hpp"
#include <sstream>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class LoggerTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(LoggerTest);
  CPPUNIT_TEST(test_debug);
  CPPUNIT_TEST(test_info);
  CPPUNIT_TEST(test_warn);
  CPPUNIT_TEST(test_error);
  CPPUNIT_TEST(test_fatal);
  CPPUNIT_TEST(test_log_debug);
  CPPUNIT_TEST(test_log_info);
  CPPUNIT_TEST(test_log_warn);
  CPPUNIT_TEST(test_log_error);
  CPPUNIT_TEST(test_log_fatal);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_debug();
  void test_info();
  void test_warn();
  void test_error();
  void test_fatal();
  void test_log_debug();
  void test_log_info();
  void test_log_warn();
  void test_log_error();
  void test_log_fatal();
};

#if 0
#define ASSERT_LOG_OUTPUT(output, level, ...)	\
  logger.log(level, __VA_ARGS__);		\
  CPPUNIT_ASSERT_EQUAL(std::string(output), oss.str()); \
  oss.str("");

void LoggerTest::test_log()
{
  std::ostringstream oss;
  {
    Logger logger(oss, Logger::LEVEL_DEBUG);
    ASSERT_LOG_OUTPUT("DEBUG: Hello.\n", Logger::LEVEL_DEBUG, "Hello.");
    ASSERT_LOG_OUTPUT("INFO: Hello.\n", Logger::LEVEL_INFO, "Hello.");
    ASSERT_LOG_OUTPUT("WARN: Hello.\n", Logger::LEVEL_WARN, "Hello.");
    ASSERT_LOG_OUTPUT("ERROR: Hello.\n", Logger::LEVEL_ERROR, "Hello.");
    ASSERT_LOG_OUTPUT("FATAL: Hello.\n", Logger::LEVEL_FATAL, "Hello.");
  }
  {
    Logger logger(oss, Logger::LEVEL_INFO);
    ASSERT_LOG_OUTPUT("", Logger::LEVEL_DEBUG, "Hello.");
    ASSERT_LOG_OUTPUT("INFO: Hello.\n", Logger::LEVEL_INFO, "Hello.");
    ASSERT_LOG_OUTPUT("WARN: Hello.\n", Logger::LEVEL_WARN, "Hello.");
    ASSERT_LOG_OUTPUT("ERROR: Hello.\n", Logger::LEVEL_ERROR, "Hello.");
    ASSERT_LOG_OUTPUT("FATAL: Hello.\n", Logger::LEVEL_FATAL, "Hello.");
  }
  {
    Logger logger(oss, Logger::LEVEL_WARN);
    ASSERT_LOG_OUTPUT("", Logger::LEVEL_DEBUG, "Hello.");
    ASSERT_LOG_OUTPUT("", Logger::LEVEL_INFO, "Hello.");
    ASSERT_LOG_OUTPUT("WARN: Hello.\n", Logger::LEVEL_WARN, "Hello.");
    ASSERT_LOG_OUTPUT("ERROR: Hello.\n", Logger::LEVEL_ERROR, "Hello.");
    ASSERT_LOG_OUTPUT("FATAL: Hello.\n", Logger::LEVEL_FATAL, "Hello.");
  }
  {
    Logger logger(oss, Logger::LEVEL_ERROR);
    ASSERT_LOG_OUTPUT("", Logger::LEVEL_DEBUG, "Hello.");
    ASSERT_LOG_OUTPUT("", Logger::LEVEL_INFO, "Hello.");
    ASSERT_LOG_OUTPUT("", Logger::LEVEL_WARN, "Hello.");
    ASSERT_LOG_OUTPUT("ERROR: Hello.\n", Logger::LEVEL_ERROR, "Hello.");
    ASSERT_LOG_OUTPUT("FATAL: Hello.\n", Logger::LEVEL_FATAL, "Hello.");
  }
  {
    Logger logger(oss, Logger::LEVEL_FATAL);
    ASSERT_LOG_OUTPUT("", Logger::LEVEL_DEBUG, "Hello.");
    ASSERT_LOG_OUTPUT("", Logger::LEVEL_INFO, "Hello.");
    ASSERT_LOG_OUTPUT("", Logger::LEVEL_WARN, "Hello.");
    ASSERT_LOG_OUTPUT("", Logger::LEVEL_ERROR, "Hello.");
    ASSERT_LOG_OUTPUT("FATAL: Hello.\n", Logger::LEVEL_FATAL, "Hello.");
  }
}
#endif

#define DEFUN_TEST_FUNC(name, output1, output2, output3, output4, output5, func, ...) \
  void LoggerTest::test_ ## name()					\
  {									\
    std::ostringstream oss;						\
    {									\
      Logger logger(oss, Logger::LEVEL_DEBUG);				\
      logger.func(__VA_ARGS__);						\
      CPPUNIT_ASSERT_EQUAL(std::string(output1), oss.str());		\
      oss.str("");							\
    }									\
    {									\
      Logger logger(oss, Logger::LEVEL_INFO);				\
      logger.func(__VA_ARGS__);						\
      CPPUNIT_ASSERT_EQUAL(std::string(output2), oss.str());		\
      oss.str("");							\
    }									\
    {									\
      Logger logger(oss, Logger::LEVEL_WARN);				\
      logger.func(__VA_ARGS__);						\
      CPPUNIT_ASSERT_EQUAL(std::string(output3), oss.str());		\
      oss.str("");							\
    }									\
    {									\
      Logger logger(oss, Logger::LEVEL_ERROR);				\
      logger.func(__VA_ARGS__);						\
      CPPUNIT_ASSERT_EQUAL(std::string(output4), oss.str());		\
      oss.str("");							\
    }									\
    {									\
      Logger logger(oss, Logger::LEVEL_FATAL);				\
      logger.func(__VA_ARGS__);						\
      CPPUNIT_ASSERT_EQUAL(std::string(output5), oss.str());		\
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

CPPUNIT_TEST_SUITE_REGISTRATION(LoggerTest);
