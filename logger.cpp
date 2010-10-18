#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <iostream>
#include "logger.hpp"

Logger &Logger::get_instance()
{
  static Logger instance(std::cout, LEVEL_DEBUG);
  return instance;
}

Logger::Logger(std::ostream &os, const LEVEL level)
  : os_(os)
  , level_(level)
{
}

static void output_prefix(std::ostream &os, const Logger::LEVEL level)
{
  switch (level) {
  case Logger::LEVEL_DEBUG:
    os << "DEBUG: ";
    break;
  case Logger::LEVEL_INFO:
    os << "INFO: ";
    break;
  case Logger::LEVEL_WARN:
    os << "WARN: ";
    break;
  case Logger::LEVEL_ERROR:
    os << "ERROR: ";
    break;
  case Logger::LEVEL_FATAL:
    os << "FATAL: ";
    break;
  }
}

void Logger::log(const Logger::LEVEL level, const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vlog(level, format, args);
  va_end(args);
}

#define DEFUN_LOGGER(name, level)		\
  void Logger::name(const char *format, ...)	\
  {						\
    va_list args;				\
    va_start(args, format);			\
    vlog(level, format, args);			\
    va_end(args);				\
  }
DEFUN_LOGGER(debug, LEVEL_DEBUG);
DEFUN_LOGGER(info, LEVEL_INFO);
DEFUN_LOGGER(warn, LEVEL_WARN);
DEFUN_LOGGER(error, LEVEL_ERROR);
DEFUN_LOGGER(fatal, LEVEL_FATAL);

void Logger::vlog(const Logger::LEVEL level, const char *format, va_list args)
{
  if (level >= level_) {
    char buf[128];
    vsnprintf(buf, sizeof buf, format, args);
    output_prefix(os_, level);
    os_ << buf << std::endl;
  }
}

