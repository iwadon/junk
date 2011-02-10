#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "texture.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <SDL.h>

class TextureTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(TextureTest);
  CPPUNIT_TEST(test_filename);
  CPPUNIT_TEST(test_load_file);
  CPPUNIT_TEST(test_width);
  CPPUNIT_TEST(test_height);
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp();
  void tearDown();
  void test_filename();
  void test_load_file();
  void test_width();
  void test_height();
private:
  SDL_Window *window_;
  SDL_Renderer *renderer_;
};

void TextureTest::setUp()
{
  window_ = SDL_CreateWindow("texture_test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 10, 10, 0);
  renderer_ = SDL_CreateRenderer(window_, -1, 0);
}

void TextureTest::tearDown()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
}

void TextureTest::test_filename()
{
  Texture tex(renderer_);
  CPPUNIT_ASSERT_EQUAL(std::string(""), tex.filename);
  tex.load_file("data/font5x5.png");
  CPPUNIT_ASSERT_EQUAL(std::string("data/font5x5.png"), tex.filename);
  tex.load_file("UNKNOWN FILE");
  CPPUNIT_ASSERT_EQUAL(std::string("data/font5x5.png"), tex.filename);
}

void TextureTest::test_load_file()
{
  Texture tex(renderer_);
  CPPUNIT_ASSERT_EQUAL(true, tex.load_file("data/font5x5.png"));
  CPPUNIT_ASSERT_EQUAL(false, tex.load_file("UNKNOWN FILE"));
}

void TextureTest::test_width()
{
  Texture tex(renderer_);
  tex.load_file("data/font5x5.png");
  CPPUNIT_ASSERT_EQUAL(256U, tex.width);
  tex.load_file("data/blue_box.png");
  CPPUNIT_ASSERT_EQUAL(100U, tex.width);
}

void TextureTest::test_height()
{
  Texture tex(renderer_);
  tex.load_file("data/font5x5.png");
  CPPUNIT_ASSERT_EQUAL(256U, tex.height);
  tex.load_file("data/blue_box.png");
  CPPUNIT_ASSERT_EQUAL(100U, tex.height);
}

CPPUNIT_TEST_SUITE_REGISTRATION(TextureTest);
