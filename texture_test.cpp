#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "texture.hpp"
#include <gtest/gtest.h>
#include <SDL.h>

class TextureTest : public ::testing::Test
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

TEST_F(TextureTest, filename)
{
  Texture tex(renderer_);
  EXPECT_EQ(std::string(""), tex.filename);
  tex.load_file("data/font5x5.png");
  EXPECT_EQ(std::string("data/font5x5.png"), tex.filename);
  tex.load_file("UNKNOWN FILE");
  EXPECT_EQ(std::string("data/font5x5.png"), tex.filename);
}

TEST_F(TextureTest, load_file)
{
  Texture tex(renderer_);
  EXPECT_EQ(true, tex.load_file("data/font5x5.png"));
  EXPECT_EQ(false, tex.load_file("UNKNOWN FILE"));
}

TEST_F(TextureTest, width)
{
  Texture tex(renderer_);
  tex.load_file("data/font5x5.png");
  EXPECT_EQ(256U, tex.width);
  tex.load_file("data/blue_box.png");
  EXPECT_EQ(100U, tex.width);
}

TEST_F(TextureTest, height)
{
  Texture tex(renderer_);
  tex.load_file("data/font5x5.png");
  EXPECT_EQ(256U, tex.height);
  tex.load_file("data/blue_box.png");
  EXPECT_EQ(100U, tex.height);
}
