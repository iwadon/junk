#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "font.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <SDL.h>

class FontTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(FontTest);
  CPPUNIT_TEST(test_draw_str);
  CPPUNIT_TEST(test_draw_strf);
  CPPUNIT_TEST(test_load_file);
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp();
  void tearDown();
  void test_draw_str();
  void test_draw_strf();
  void test_load_file();
private:
  SDL_Window *window_;
  SDL_Renderer *renderer_;
};

void FontTest::setUp()
{
  window_ = SDL_CreateWindow("texture_test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 10, 10, 0);
  CPPUNIT_ASSERT(window_ != NULL);
  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  CPPUNIT_ASSERT(renderer_ != NULL);
}

void FontTest::tearDown()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
}

void FontTest::test_draw_str()
{
  Font font(renderer_);
  CPPUNIT_ASSERT(font.renderer() != NULL);
  CPPUNIT_ASSERT_EQUAL(true, font.load_file("data/font5x5.png"));
  font.draw_str(0, 0, "Hello.");
}

void FontTest::test_draw_strf()
{
  Font font(renderer_);
  CPPUNIT_ASSERT_EQUAL(true, font.load_file("data/font5x5.png"));
  font.draw_strf(0, 0, "%s %d %f", "Hello.", 12345, 67.89f);
}

void FontTest::test_load_file()
{
  Font font(renderer_);
  CPPUNIT_ASSERT_EQUAL(true, font.load_file("data/font5x5.png"));
  CPPUNIT_ASSERT_EQUAL(false, font.load_file("UNKNOWN FILE"));
}

CPPUNIT_TEST_SUITE_REGISTRATION(FontTest);
