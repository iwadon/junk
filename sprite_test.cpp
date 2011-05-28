#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sprite.hpp"
#include <gtest/gtest.h>
#include <SDL.h>

class SpriteTest : public ::testing::Test
{
protected:
  SDL_Window *window_;
  SDL_Renderer *renderer_;

  void SetUp();
  void TearDown();
};

void SpriteTest::SetUp()
{
  window_ = NULL;
  renderer_ = NULL;
  window_ = SDL_CreateWindow("texture_test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 10, 10, 0);
  ASSERT_TRUE(window_ != NULL);
  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  ASSERT_TRUE(renderer_ != NULL);
}

void SpriteTest::TearDown()
{
  SDL_DestroyRenderer(renderer_);
  renderer_ = NULL;
  SDL_DestroyWindow(window_);
  window_ = NULL;
}

TEST_F(SpriteTest, set_texture)
{
  Sprite s(renderer_);
  SDL_Rect r = {10, 10, 20, 20};
  ASSERT_TRUE(s.set_texture("data/blue_box.png"));
  ASSERT_TRUE(s.set_texture("data/blue_box.png", &r));
  ASSERT_FALSE(s.set_texture("UNKNOWN FILE"));
  ASSERT_FALSE(s.set_texture("UNKNOWN FILE", &r));
}

TEST_F(SpriteTest, draw)
{
  Sprite s(renderer_);
  s.set_texture("data/blue_box.png");
  s.draw();
}
