#ifndef LOAD_TIME_HPP_INCLUDED
#define LOAD_TIME_HPP_INCLUDED 1

#include <list>
#include <tr1/cstdint>

class Font;

class LoadTime
{
public:
  typedef uint32_t time_type;
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
private:
  struct Item
  {
    time_type start;
    time_type end;
    time_type elapsed;
    uint8_t color[4];
    char *name;
    bool is_running() const { return start != 0; }
  };
  Item items_[NUM_ITEMS];
  std::list <Item *> active_items_;
};

#endif // !defined(LOAD_TIME_HPP_INCLUDED)