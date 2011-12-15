#ifndef OBSERVER_HPP_INCLUDED
#define OBSERVER_HPP_INCLUDED 1

#include <cassert>
#include <algorithm>
#include <list>
#include <boost/foreach.hpp>

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

  Subject()
    : notifying_(false)
  {
  }

  virtual ~Subject()
  {
    notify();
  }

  void attach(observer_type *o)
  {
    assert(o != NULL);
    typename observer_list_type::iterator i = std::find(observers_.begin(), observers_.end(), o);
    if (i == observers_.end()) {
      observers_.push_back(o);
    }
  }

  void detach(observer_type *o)
  {
    assert(o != NULL);
    if (notifying_) {
      detached_observers_.push_back(o);
    } else {
      detach_observer(o);
    }
  }

  void notify()
  {
    notifying_ = true;
    BOOST_FOREACH(observer_type *o, observers_) {
      o->update(this);
    }
    notifying_ = false;
    BOOST_FOREACH(observer_type *o, detached_observers_) {
      detach_observer(o);
    }
    detached_observers_.clear();
  }

private:
  observer_list_type observers_;
  observer_list_type detached_observers_;
  bool notifying_;
  void detach_observer(observer_type *o)
  {
    typename observer_list_type::iterator i = std::find(observers_.begin(), observers_.end(), o);
    if (i != observers_.end()) {
      observers_.erase(i);
    }
  }
};

#endif // !defined(OBSERVER_HPP_INCLUDED)
