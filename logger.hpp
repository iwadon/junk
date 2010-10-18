#ifndef LOGGER_HPP_INCLUDED
#define LOGGER_HPP_INCLUDED

#include <cstdarg>
#include <ostream>
#ifdef HAVE_BOOST
#include <boost/noncopyable.hpp>
#endif

class Logger : public boost::noncopyable
{
public:
  enum LEVEL {
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARN,
    LEVEL_ERROR,
    LEVEL_FATAL,
  };
  static Logger &get_instance();
  Logger(std::ostream &os, const LEVEL level);
  void log(const LEVEL level, const char *format, ...);
  void debug(const char *format, ...);
  void info(const char *format, ...);
  void warn(const char *format, ...);
  void error(const char *format, ...);
  void fatal(const char *format, ...);
protected:
  void vlog(const Logger::LEVEL, const char *format, va_list args);
private:
  std::ostream &os_;
  LEVEL level_;
};

#define glogger Logger::get_instance()

#endif // !defined(LOGGER_HPP_INCLUDED)
