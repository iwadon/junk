#ifndef FRAME_WAIT_TIMER_HPP_INCLUDED
#define FRAME_WAIT_TIMER_HPP_INCLUDED

class FrameWaitTimer
{
public:
  FrameWaitTimer(const int fps, const int max_skip_frames);
  void reset();
  int wait();
  void set_fps(const int new_fps) { fps_ = new_fps; }
private:
  int fps_;
  int max_skip_frames_;
  float prev_ticks_;
};

#endif // !defined(FRAME_WAIT_TIMER_HPP_INCLUDED)
