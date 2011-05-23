#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "texture_pool.hpp"
#include <gtest/gtest.h>
#include <SDL.h>

class TexturePoolTest : public ::testing::Test
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

TEST_F(TexturePoolTest, load_file)
{
  Texture *tex;
  tex = TexturePool::get_instance().load_file(renderer_, "data/font5x5.png");
  ASSERT_TRUE(tex != NULL);
  tex = TexturePool::get_instance().load_file(renderer_, "UNKNOWN FILE");
  ASSERT_TRUE(tex == NULL);
}
