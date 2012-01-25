#include <stdio.h>
#include <SDL.h>
#include "sdl_logger.h"

int main(int argc, char *argv[])
{
#pragma unused(argc, argv)
  SDL_Window *window;
  SDL_Renderer *renderer;
  int done = 0;
  SDL_Event event;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_ERROR(SDL_Init);
    return 1;
  }
  if (SDL_CreateWindowAndRenderer(200, 200, 0, &window, &renderer) == -1) {
    SDL_ERROR(SDL_SetVideoMode);
    SDL_Quit();
    return 1;
  }
  while (!done) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT ||
	  (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q && (event.key.keysym.mod == KMOD_LGUI || event.key.keysym.mod == KMOD_RGUI))) {
	done = !0;
      }
    }
    SDL_Delay(0);
  }
  SDL_Delay(500);
  SDL_Quit();
  return 0;
}
