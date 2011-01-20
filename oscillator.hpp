#ifndef OSCILLATOR_HPP_INCLUDED
#define OSCILLATOR_HPP_INCLUDED 1

/**
 * @brief 波形データ生成クラスの基底クラス
 *
 * @sa SineWaveOscillator
 * @sa TriangleWaveOscillator
 * @sa SawWaveOscillator
 * @sa SquareWaveOscillator
 */
class Oscillator
{
public:
  Oscillator();
  virtual ~Oscillator() {}
  virtual float value() = 0;
  float sample_rate() const { return sample_rate_; }
  virtual void set_sample_rate(const float rate);
  float frequency() const { return frequency_; }
  virtual void set_frequency(const float freq);
protected:
  virtual void setup() {}
private:
  float sample_rate_;
  float frequency_;
};

#endif // !defined(OSCILLATOR_HPP_INCLUDED)
