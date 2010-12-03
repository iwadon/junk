#ifndef CHANNEL_HPP_INCLUDED
#define CHANNEL_HPP_INCLUDED 1

class Channel
{
public:
  virtual void note_on(int note, int velocity);
  virtual void note_off(int note, int velocity);
  virtual void polyphonic_pressure(int note, int velocity);
  virtual void control_change(int no, int value);
  virtual void program_change(int no);
  virtual void channel_pressure(int no);
  virtual void pitch_bend_change(int value);
};

#endif // !defined(CHANNEL_HPP_INCLUDED)
