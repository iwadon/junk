#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "fps.hpp"
#include <gtest/gtest.h>
#include <SDL.h>

class FpsTest : public ::testing::Test
{
protected:
  SDL_Window *window_;
  SDL_Renderer *renderer_;

  void SetUp()
  {
    window_ = NULL;
    renderer_ = NULL;
    int ret = SDL_Init(SDL_INIT_TIMER);
    ASSERT_EQ(0, ret);
    window_ = SDL_CreateWindow("TextureTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 10, 10, 0);
    ASSERT_TRUE(window_ != NULL);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);
    ASSERT_TRUE(renderer_ != NULL);
  }

  void TearDown()
  {
    SDL_DestroyRenderer(renderer_);
    renderer_ = NULL;
    SDL_DestroyWindow(window_);
    window_ = NULL;
    SDL_Quit();
  }
};

TEST_F(FpsTest, update)
{
  FPS fps;
  fps.next_ticks = SDL_GetTicks() + 1000;
  for (int i = 0; i < 9; ++i) {
    SDL_Delay(100);
    fps.update();
    EXPECT_EQ(static_cast<uint32_t>(i + 1), fps.frames);
    EXPECT_EQ(0U, fps.latest_frames);
  }
  SDL_Delay(100 + 50);
  fps.update();
  EXPECT_EQ(0U, fps.frames);
  EXPECT_EQ(10U, fps.latest_frames);
}
