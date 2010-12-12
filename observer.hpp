#ifndef OBSERVER_HPP_INCLUDED
#define OBSERVER_HPP_INCLUDED 1

#ifdef STDCXX_98_HEADERS
#include <list>
#endif
#ifdef HAVE_BOOST
#include <boost/foreach.hpp>
#endif

class Observer
{
public:
  virtual ~Observer() {}
  virtual void notify() {}
};

class Subject
{
public:
  void add_observer(Observer *o)
  {
    observers_.push_back(o);
  }

  void remove_observer(Observer *o)
  {
    observers_.remove(o);
  }

  void notify_observers()
  {
    BOOST_FOREACH(Observer *o, observers_) {
      o->notify();
    }
  }
private:
  std::list<Observer *> observers_;
};

#endif // !defined(OBSERVER_HPP_INCLUDED)
