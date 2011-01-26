#ifndef PATCH_HPP_INCLUDED
#define PATCH_HPP_INCLUDED 1

class Oscillator;

class Patch
{
public:
  Patch();
  Oscillator *oscillator() { return oscillator_; }
  void set_oscillator(Oscillator *oscillator);
private:
  Oscillator *oscillator_;
};

#endif // !defined(PATCH_HPP_INCLUDED)
