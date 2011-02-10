#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sprite.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <SDL.h>

class SpriteTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(SpriteTest);
  CPPUNIT_TEST(test_set_texture);
  CPPUNIT_TEST(test_draw);
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp();
  void tearDown();
  void test_set_texture();
  void test_draw();
private:
  SDL_Window *window_;
  SDL_Renderer *renderer_;
};

void SpriteTest::setUp()
{
  window_ = SDL_CreateWindow("texture_test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 10, 10, 0);
  renderer_ = SDL_CreateRenderer(window_, -1, 0);
}

void SpriteTest::tearDown()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
}

void SpriteTest::test_set_texture()
{
  Sprite s(renderer_);
  SDL_Rect r = {10, 10, 20, 20};
  CPPUNIT_ASSERT_EQUAL(true, s.set_texture("data/blue_box.png"));
  CPPUNIT_ASSERT_EQUAL(true, s.set_texture("data/blue_box.png", &r));
  CPPUNIT_ASSERT_EQUAL(false, s.set_texture("UNKNOWN FILE"));
  CPPUNIT_ASSERT_EQUAL(false, s.set_texture("UNKNOWN FILE", &r));
}

void SpriteTest::test_draw()
{
  Sprite s(renderer_);
  s.set_texture("data/blue_box.png");
  s.draw();
}

CPPUNIT_TEST_SUITE_REGISTRATION(SpriteTest);
