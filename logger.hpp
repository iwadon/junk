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
  void set_level(const LEVEL level) { level_ = level; }
protected:
  void vlog(const Logger::LEVEL, const char *format, va_list args);
private:
  std::ostream &os_;
  LEVEL level_;
};

#define DEBUG(...) Logger::get_instance().debug(__VA_ARGS__)
#define INFO(...) Logger::get_instance().info(__VA_ARGS__)
#define WARN(...) Logger::get_instance().warn(__VA_ARGS__)
#define ERROR(...) Logger::get_instance().error(__VA_ARGS__)
#define FATAL(...) Logger::get_instance().fatal(__VA_ARGS__)

#endif // !defined(LOGGER_HPP_INCLUDED)
