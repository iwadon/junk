#ifndef OBJECT_COUNTER_HPP_INCLUDED
#define OBJECT_COUNTER_HPP_INCLUDED 1

// Object counter using CRTP(curiously recurring template pattern)
// http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern#Object_counter
template <typename T>
struct ObjectCounter
{
  static int created;
  static int alive;
  ObjectCounter()
  {
    ++created;
    ++alive;
  }
protected:
  ~ObjectCounter()
  {
    --alive;
  }
};
template <typename T> int ObjectCounter<T>::created(0);
template <typename T> int ObjectCounter<T>::alive(0);

#endif // !defined(OBJECT_COUNTER_HPP_INCLUDED)
