#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

enum LOGGER_LEVEL {
  LOGGER_LEVEL_DEBUG,
  LOGGER_LEVEL_INFO,
  LOGGER_LEVEL_WARN,
  LOGGER_LEVEL_ERROR,
  LOGGER_LEVEL_FATAL,
  NUM_LOGGER_LEVELS
};

void logger_vlog(const enum LOGGER_LEVEL level, const char *message, va_list args);
void logger_log(const enum LOGGER_LEVEL level, const char *message, ...);
void logger_debug(const char *message, ...);
void logger_info(const char *message, ...);
void logger_warn(const char *message, ...);
void logger_error(const char *message, ...);
void logger_fatal(const char *message, ...);

#define DEBUG(...) logger_debug(__VA_ARGS__)
#define INFO(...) logger_(__VA_ARGS__)
#define WARN(...) logger_warn(__VA_ARGS__)
#define ERROR(...) logger_error(__VA_ARGS__)
#define FATAL(...) logger_fatal(__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif // !defined(LOGGER_H_INCLUDED)
