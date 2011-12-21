// Observerパターンの実装で、notify中にdetachする処理の実装の違いを速度で比べてみる

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
// 実装1: notify中にdetachしようとしたobserverを一旦保留して、あとから一挙にdetachする。
#define Observer Observer1
#define Subject Subject1
#include "observer.hpp"
#undef Observer
#undef Subject
// 実装2: 複製したリストを回してnotifyする。
#define Observer Observer2
#define Subject Subject2
#include "observer_2.hpp"
#undef Observer
#undef Subject
// 実装3: observer::update()の戻り値がfalseならばdetachする。observer::update()内で明示的にdetachしない。
#define Observer Observer3
#define Subject Subject3
#include "observer_3.hpp"
#undef Observer
#undef Subject
#include "benchmark.hpp"

class S1 : public Subject1<S1>
{
};
class O1 : public Observer1<S1>
{
  void update(Subject1<S1> *subject)
  {
    subject->detach(this);
  }
};

class S2 : public Subject2<S2>
{
};
class O2 : public Observer2<S2>
{
  void update(Subject2<S2> *subject)
  {
    subject->detach(this);
  }
};

class S3 : public Subject3<S3>
{
};
class O3 : public Observer3<S3>
{
  bool update(Subject3<S3> */*subject*/)
  {
    return false;
  }
};

template <typename O, typename S>
static void case1()
{
  O o;
  S s;
  s.attach(&o);
  s.detach(&o);
}

template <typename O, typename S>
static void case2()
{
  O o;
  S s;
  s.attach(&o);
  s.notify();
}

int main()
{
  BM(1-1, (case1<O1, S1>()));
  BM(1-2, (case2<O1, S1>()));
  BM(2-1, (case1<O2, S2>()));
  BM(2-2, (case2<O2, S2>()));
  BM(3-1, (case1<O3, S3>()));
  BM(3-2, (case2<O3, S3>()));
  return 0;
}
