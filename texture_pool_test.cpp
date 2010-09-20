#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "texture_pool.hpp"

class TexturePoolTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(TexturePoolTest);
  CPPUNIT_TEST(test_load_file);
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp();
  void tearDown();
  void test_load_file();
private:
  SDL_Window *window_;
};

void TexturePoolTest::setUp()
{
  window_ = SDL_CreateWindow("texture_test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 10, 10, 0);
  SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTFLIP3);
}

void TexturePoolTest::tearDown()
{
  SDL_DestroyWindow(window_);
}

void TexturePoolTest::test_load_file()
{
  Texture *tex;
  tex = TexturePool::get_instance().load_file("data/font5x5.png");
  CPPUNIT_ASSERT(tex != NULL);
  tex = TexturePool::get_instance().load_file("UNKNOWN FILE");
  CPPUNIT_ASSERT(tex == NULL);
}

CPPUNIT_TEST_SUITE_REGISTRATION(TexturePoolTest);
