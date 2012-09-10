#ifndef SOUND_HPP_INCLUDED
#define SOUND_HPP_INCLUDED 1

#include <list>
#include <SDL.h>
#include "sp.hpp"

class VoiceBase;

class Sound
{
public:
  typedef int32_t Handle;
  static const Handle INVALID_HANDLE = -1;

  static const int RESULT_OK = 0;
  static const int RESULT_ERROR = -1;

  Sound();
  ~Sound();
  int Initialize();
  void Finalize();
  void Update();

  int StartServer();
  int StopServer();

  bool LoadSndFile(const SP &filename);

  int Play(int label);

protected:
  static void AudioCallback(void *userdata, uint8_t *stream, int len);
  void MixAudio(void *buf, int len);

private:
  SDL_AudioSpec audio_spec_;
  std::list<void *> snd_files_;
  std::list<VoiceBase *> voices_;

  bool InitializeAudio();
  void FinalizeAudio();
  void LogAudioDrivers();
  void LogAudioSpec();
};

#endif // !defined(SOUND_HPP_INCLUDED)
