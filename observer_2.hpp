#ifndef OBSERVER_2_HPP_INCLUDED
#define OBSERVER_2_HPP_INCLUDED 1

#include <algorithm>
#include <cassert>
#include <list>

template <typename T> class Subject;

template <typename T>
class Observer
{
public:
  virtual ~Observer() {}
  virtual void update(Subject<T> *subject) = 0;
};

template <typename T>
class Subject
{
public:
  typedef Observer<T> observer_type;
  typedef std::list<observer_type *> observer_list_type;
  virtual ~Subject() { notify(); }
  void attach(observer_type *o);
  void detach(observer_type *o);
  void notify();

private:
  observer_list_type observers_;
  void detach_observer(observer_type *o);
};

template <typename T>
inline void Subject<T>::attach(observer_type *o)
{
  assert(o != NULL);
  typename observer_list_type::iterator i = std::find(observers_.begin(), observers_.end(), o);
  if (i == observers_.end()) {
    observers_.push_back(o);
  }
}

template <typename T>
inline void Subject<T>::detach(observer_type *o)
{
  assert(o != NULL);
  detach_observer(o);
}

template <typename T>
inline void Subject<T>::notify()
{
  observer_list_type l(observers_.begin(), observers_.end());
  for (auto o: l) {
    o->update(this);
  }
}

template <typename T>
inline void Subject<T>::detach_observer(observer_type *o)
{
  observers_.remove(o);
}

#endif // !defined(OBSERVER_2_HPP_INCLUDED)
