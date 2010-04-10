#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "volume.hpp"

class VolumeTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(VolumeTest);
  CPPUNIT_TEST(test_is_updated);
  CPPUNIT_TEST(test_set);
  CPPUNIT_TEST(test_update);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_is_updated();
  void test_set();
  void test_update();
};

void VolumeTest::test_is_updated()
{
  Volume<float, int32_t> v(0.0f);
  CPPUNIT_ASSERT_EQUAL(false, v.is_updated());
  v.update();
  CPPUNIT_ASSERT_EQUAL(false, v.is_updated());
  v.set(1.0f);
  CPPUNIT_ASSERT_EQUAL(false, v.is_updated());
  v.update();
  CPPUNIT_ASSERT_EQUAL(true, v.is_updated());
  v.update();
  CPPUNIT_ASSERT_EQUAL(false, v.is_updated());
  v.set(2.0f, 2);
  v.update();
  CPPUNIT_ASSERT_EQUAL(true, v.is_updated());
  v.update();
  CPPUNIT_ASSERT_EQUAL(true, v.is_updated());
  v.update();
  CPPUNIT_ASSERT_EQUAL(false, v.is_updated());
}

void VolumeTest::test_set()
{
  Volume<float, int32_t> v(0.0f);
  v.set(1.0f);
  CPPUNIT_ASSERT_EQUAL(1.0f, v.get());
  v.set(2.0f, 1);
  CPPUNIT_ASSERT_EQUAL(1.0f, v.get());
  v.update();
  CPPUNIT_ASSERT_EQUAL(2.0f, v.get());
}

void VolumeTest::test_update()
{
  Volume<float, int32_t> v(0.0f);
  v.set(1.0f, 2);
  CPPUNIT_ASSERT_EQUAL(0.0f, v.get());
  v.update();
  CPPUNIT_ASSERT_EQUAL(0.5f, v.get());
  v.update();
  CPPUNIT_ASSERT_EQUAL(1.0f, v.get());
  v.update();
  CPPUNIT_ASSERT_EQUAL(1.0f, v.get());
}

CPPUNIT_TEST_SUITE_REGISTRATION(VolumeTest);
