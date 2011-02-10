#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "fps.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <SDL.h>

class FpsTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(FpsTest);
  CPPUNIT_TEST(test_update);
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp();
  void tearDown();
  void test_update();
private:
  SDL_Window *window_;
  SDL_Renderer *renderer_;
};

void FpsTest::setUp()
{
  SDL_Init(SDL_INIT_TIMER);
  window_ = SDL_CreateWindow("fps_test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 10, 10, 0);
  renderer_ = SDL_CreateRenderer(window_, -1, 0);
}

void FpsTest::tearDown()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

void FpsTest::test_update()
{
  FPS fps;
  fps.next_ticks = SDL_GetTicks() + 1000;
  for (int i = 0; i < 9; ++i) {
    SDL_Delay(100);
    fps.update();
    CPPUNIT_ASSERT_EQUAL(static_cast<uint32_t>(i + 1), fps.frames);
    CPPUNIT_ASSERT_EQUAL(0U, fps.latest_frames);
  }
  SDL_Delay(100 + 50);
  fps.update();
  CPPUNIT_ASSERT_EQUAL(0U, fps.frames);
  CPPUNIT_ASSERT_EQUAL(10U, fps.latest_frames);
}

CPPUNIT_TEST_SUITE_REGISTRATION(FpsTest);
