#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "sprite.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class SpriteTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(SpriteTest);
  CPPUNIT_TEST(test_load_texture_file);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_load_texture_file();
};

void SpriteTest::test_load_texture_file()
{
  Sprite s;
  CPPUNIT_ASSERT_EQUAL(true, s.load_texture_file("data/blue_box.png"));
  CPPUNIT_ASSERT_EQUAL(false, s.load_texture_file("UNKNOWN FILE"));
}

CPPUNIT_TEST_SUITE_REGISTRATION(SpriteTest);
