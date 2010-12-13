#ifndef OBSERVER_HPP_INCLUDED
#define OBSERVER_HPP_INCLUDED 1

#ifdef STDCXX_98_HEADERS
#include <list>
#endif
#ifdef HAVE_BOOST
#include <boost/foreach.hpp>
#endif

class Subject;

class Observer
{
public:
  virtual ~Observer() {}
  virtual void update(Subject *subject) = 0;
};

class Subject
{
public:
  void attach(Observer *o)
  {
    observers_.push_back(o);
  }

  void detach(Observer *o)
  {
    observers_.remove(o);
  }

  void notify()
  {
    BOOST_FOREACH(Observer *o, observers_) {
      o->update(this);
    }
  }
private:
  std::list<Observer *> observers_;
};

#endif // !defined(OBSERVER_HPP_INCLUDED)
