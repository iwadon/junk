#include "pad.hpp"
#include <cstring>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>

const PadData PadData::ZERO = {{0.0f, 0.0f}, {0.0f, 0.0f}, 0u};

std::string PadData::to_string() const
{
  char buf[36];
  snprintf(buf, sizeof buf, "%5.2f %5.2f %5.2f %5.2f 0x%08x", al.x, al.y, ar.x, ar.y, button);
  return buf;
}

namespace {

  struct KEY_ASSIGN
  {
    SDL_Scancode scancode;
    PAD_BUTTON button;
  };

  const KEY_ASSIGN key_assigns[] = {
    {SDL_SCANCODE_W, PAD_BUTTON_U},
    {SDL_SCANCODE_S, PAD_BUTTON_D},
    {SDL_SCANCODE_A, PAD_BUTTON_L},
    {SDL_SCANCODE_D, PAD_BUTTON_R},
    {SDL_SCANCODE_UP, PAD_BUTTON_U},
    {SDL_SCANCODE_DOWN, PAD_BUTTON_D},
    {SDL_SCANCODE_LEFT, PAD_BUTTON_L},
    {SDL_SCANCODE_RIGHT, PAD_BUTTON_R},
    {SDL_SCANCODE_SPACE, PAD_BUTTON_A},
    {SDL_SCANCODE_LSHIFT, PAD_BUTTON_SLOW},
    {SDL_SCANCODE_RSHIFT, PAD_BUTTON_SLOW},
    {SDL_SCANCODE_LCTRL, PAD_BUTTON_FAST},
    {SDL_SCANCODE_RETURN, PAD_BUTTON_START}
  };

} // unnamed namespace

/**
 * @brief 更新
 *
 * キーボードからの入力を元にパッドデータを作る。
 */
void HumanPad::on_update()
{
  button = 0;
  const uint8_t *key_states = SDL_GetKeyboardState(NULL);
  for (auto &ka: key_assigns) {
    if (key_states[ka.scancode]) {
      button |= ka.button;
    }
  }
}
