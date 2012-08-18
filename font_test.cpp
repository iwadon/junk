#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "font.hpp"
#include <gtest/gtest.h>
#include <SDL.h>

class FontTest : public ::testing::Test
{
protected:
  SDL_Window *window_;
  SDL_Renderer *renderer_;

  void SetUp()
  {
    window_ = NULL;
    renderer_ = NULL;
    window_ = SDL_CreateWindow("TextureTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 10, 10, 0);
    ASSERT_TRUE(window_ != NULL);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);
    ASSERT_TRUE(renderer_ != NULL);
  }

  void TearDown()
  {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    renderer_ = NULL;
    window_ = NULL;
  }
};

TEST_F(FontTest, draw_str)
{
  Font font(renderer_);
  ASSERT_TRUE(font.renderer() != NULL);
  ASSERT_EQ(true, font.load_file("data/font5x5.png"));
  font.draw_str(0, 0, "Hello.");
}

TEST_F(FontTest, draw_strf)
{
  Font font(renderer_);
  ASSERT_EQ(true, font.load_file("data/font5x5.png"));
  font.draw_strf(0, 0, "%s %d %f", "Hello.", 12345, 67.89f);
}

TEST_F(FontTest, load_file)
{
  Font font(renderer_);
  ASSERT_TRUE(font.load_file("data/font5x5.png"));
  ASSERT_TRUE(!font.load_file("UNKNOWN FILE"));
}
