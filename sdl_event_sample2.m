#if defined(__APPLE__) && defined(__BLOCKS__)

#import <Cocoa/Cocoa.h>
#include <stdio.h>
#include <SDL.h>

#define SDL_ERROR(func) fprintf(stderr, #func "() failed: %s\n", SDL_GetError())

#endif // defined(__APPLE__) && defined(__BLOCKS__)

int main(int argc, char *argv[])
{
#pragma unused(argc, argv)
#if defined(__APPLE__) && defined(__BLOCKS__)
  SDL_Window *window;
  SDL_Renderer *renderer;
  int done = 0;
  SDL_Event event;

  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

  [NSEvent addLocalMonitorForEventsMatchingMask:NSKeyDownMask
					handler:(^(NSEvent* event) {
					    NSLog(@"LocalMonitor: %@", event);
					    return event;
					  })];

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_ERROR(SDL_Init);
    [pool release];
    return 1;
  }
  if (SDL_CreateWindowAndRenderer(200, 200, 0, &window, &renderer) == -1) {
    SDL_ERROR(SDL_SetVideoMode);
    SDL_Quit();
    [pool release];
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
  [pool release];
#endif // defined(__APPLE__) && defined(__BLOCKS__)
  return 0;
}
