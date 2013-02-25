#ifndef LOAD_TIME_HPP_INCLUDED
#define LOAD_TIME_HPP_INCLUDED 1

#include <cstddef>
#include <list>
#ifdef _MSC_VER
#include <cstdint>
#else
#include <tr1/cstdint>
#endif

class Font;

class LoadTime
{
public:
  typedef uint64_t time_type;
  static const time_type TIME_BASE_SEC = 1000 * 1000 * 1000;
  static const time_type TIME_BASE_MILLISEC = 1000 * 1000;
  static const size_t NUM_ITEMS = 10;
  LoadTime();
  ~LoadTime();
  void start(const size_t no);
  void stop(const size_t no);
  void flip();
  time_type elapsed_time(const size_t no) const;
  void set_color(const size_t no, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);
  void set_name(const size_t no, const char *name);
  void draw(Font *font, const int x, const int y) const;
  void activate(const size_t no);
private:
  struct Item
  {
    typedef uint32_t FLAG;
    static const FLAG FLAG_DIRTY  = 1 << 0;
    static const FLAG FLAG_ACTIVE = 1 << 1;
    time_type start;
    time_type end;
    time_type elapsed;
    time_type last_elapsed;
    uint8_t color[4];
    FLAG flags;
    char *name;
    bool is_running() const { return start != 0; }
  };
  Item items_[NUM_ITEMS];
  std::list <Item *> active_items_;
  uint64_t freq_;
  time_type get_elapsed_time(time_type end, time_type start) const;
};

#endif // !defined(LOAD_TIME_HPP_INCLUDED)
