#ifndef CHANNEL_HPP_INCLUDED
#define CHANNEL_HPP_INCLUDED 1

class Channel
{
public:
  void note_on(int note, int velocity);
  void note_off(int note, int velocity);
  void polyphonic_pressure(int note, int velocity);
  void control_change(int no, int value);
  void program_change(int no);
  void channel_pressure(int no);
  void pitch_bend_change(int value);
};

#endif // !defined(CHANNEL_HPP_INCLUDED)
