#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "smf.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <SDL.h>
#include "song.hpp"

class SmfTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(SmfTest);
  CPPUNIT_TEST(test_is_playing);
  CPPUNIT_TEST(test_set_data);
  CPPUNIT_TEST(test_play);
  CPPUNIT_TEST(test_update);
#ifdef SMF_DEBUG
  CPPUNIT_TEST(test_inspect);
#endif
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp();
  void tearDown();
  void test_is_playing();
  void test_set_data();
  void test_play();
  void test_update();
#ifdef SMF_DEBUG
  void test_inspect();
#endif
private:
  void *data_;
};

static std::string format(const char *format, ...)
{
  char buf[256];
  va_list args;
  va_start(args, format);
  vsnprintf(buf, sizeof buf, format, args);
  va_end(args);
  std::string result(buf);
  return result;
}

void SmfTest::setUp()
{
  SDL_RWops *ctx = SDL_RWFromFile("data/sample.mid", "rb");
  CPPUNIT_ASSERT(ctx != NULL);
  size_t len = SDL_RWseek(ctx, 0, RW_SEEK_END);
  SDL_RWseek(ctx, 0, RW_SEEK_SET);
  data_ = SDL_malloc(len);
  CPPUNIT_ASSERT(data_ != NULL);
  int ret = SDL_RWread(ctx, data_, len, 1);
  CPPUNIT_ASSERT(ret == 1);
  ret = SDL_RWclose(ctx);
  CPPUNIT_ASSERT(ret != -1);
}

void SmfTest::tearDown()
{
  SDL_free(data_);
  data_ = NULL;
}

void SmfTest::test_is_playing()
{
  Song song;
  SMF smf(song);
  CPPUNIT_ASSERT_EQUAL(false, smf.is_playing());
  smf.set_data(data_);
  CPPUNIT_ASSERT_EQUAL(false, smf.is_playing());
}

void SmfTest::test_set_data()
{
  Song song;
  SMF smf(song);
  CPPUNIT_ASSERT_EQUAL(true, smf.set_data(data_));
}

void SmfTest::test_play()
{
}

void SmfTest::test_update()
{
}

#ifdef SMF_DEBUG
void SmfTest::test_inspect()
{
  Song song;
  SMF smf(song);
  CPPUNIT_ASSERT_EQUAL(format("#<SMF:%p format 0, 0 track(s), timebase=48>", &smf), smf.inspect());
  smf.set_data(data_);
  CPPUNIT_ASSERT_EQUAL(format("#<SMF:%p format 1, 2 track(s), timebase=480>", &smf), smf.inspect());
}
#endif

CPPUNIT_TEST_SUITE_REGISTRATION(SmfTest);
