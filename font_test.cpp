#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "font.hpp"

class FontTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(FontTest);
  CPPUNIT_TEST(test_draw);
  CPPUNIT_TEST(test_load_file);
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp();
  void tearDown();
  void test_draw();
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
  SDL_DestroyWindow(window_);
}

void FontTest::test_draw()
{
  Font font;
  font.load_file("data/font5x5.png");
  font.draw(window_, 0, 0, "Hello.");
}

void FontTest::test_load_file()
{
  Font font;
  CPPUNIT_ASSERT_EQUAL(true, font.load_file("data/font5x5.png"));
  CPPUNIT_ASSERT_EQUAL(false, font.load_file("UNKNOWN FILE"));
}

CPPUNIT_TEST_SUITE_REGISTRATION(FontTest);
