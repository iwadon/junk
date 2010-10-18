#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "font.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#ifdef HAVE_SDL_H
#include <SDL.h>
#endif

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
};

void FontTest::setUp()
{
  window_ = SDL_CreateWindow("texture_test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 10, 10, 0);
  SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTFLIP3);
}

void FontTest::tearDown()
{
  SDL_DestroyRenderer(window_);
  SDL_DestroyWindow(window_);
}

void FontTest::test_draw_str()
{
  Font font;
  font.load_file("data/font5x5.png");
  font.draw_str(0, 0, "Hello.");
}

void FontTest::test_draw_strf()
{
  Font font;
  font.load_file("data/font5x5.png");
  font.draw_strf(0, 0, "%s %d %f", "Hello.", 12345, 67.89f);
}

void FontTest::test_load_file()
{
  Font font;
  CPPUNIT_ASSERT_EQUAL(true, font.load_file("data/font5x5.png"));
  CPPUNIT_ASSERT_EQUAL(false, font.load_file("UNKNOWN FILE"));
}

CPPUNIT_TEST_SUITE_REGISTRATION(FontTest);
