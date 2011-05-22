#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "logger.h"
#include <stdarg.h>
#include <stdio.h>

#ifdef NDEBUG
static enum LOGGER_LEVEL logger_level = LOGGER_LEVEL_INFO;
#else
static enum LOGGER_LEVEL logger_level = LOGGER_LEVEL_DEBUG;
#endif

static const char *logger_prefix(const enum LOGGER_LEVEL level)
{
  static const char *level_str[NUM_LOGGER_LEVELS] = {
    "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
  };
  return level_str[level];
}

void logger_vlog(const enum LOGGER_LEVEL level, const char *message, va_list args)
{
  if (level >= logger_level) {
    printf("%s: ", logger_prefix(level));
    vprintf(message, args);
    puts("\n");
  }
}

void logger_log(const enum LOGGER_LEVEL level, const char *message, ...)
{
  va_list args;
  va_start(args, message);
  logger_vlog(level, message, args);
  va_end(args);
}

#define DEFUN_LOGGER(name, level)			\
  void logger_ ## name(const char *message, ...) {	\
    va_list args;					\
    va_start(args, message);				\
    logger_vlog(level, message, args);			\
    va_end(args);					\
  }
DEFUN_LOGGER(debug, LOGGER_LEVEL_DEBUG);
DEFUN_LOGGER(info, LOGGER_LEVEL_INFO);
DEFUN_LOGGER(warn, LOGGER_LEVEL_WARN);
DEFUN_LOGGER(error, LOGGER_LEVEL_DEBUG);
DEFUN_LOGGER(fatal, LOGGER_LEVEL_FATAL);
#undef DEFUN_LOGGER
