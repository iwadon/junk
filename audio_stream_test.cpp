#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "vector.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class TestAudioStream
{
public:
  TestAudioStream()
    : n_(0)
    , m_(0.0f)
  {
  }
  virtual size_t read(uint8_t *buf, size_t len, float ratio)
  {
    for (size_t i = 0; i < len; ++i) {
      buf[i] = n_ + m_;
      m_ += ratio;
    }
    return len;
  }
private:
  uint8_t n_;
  float m_;
};

class AudioStreamTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(AudioStreamTest);
  CPPUNIT_TEST(test_read);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_read();
};

void AudioStreamTest::test_read()
{
  TestAudioStream as;
  uint8_t buf[10];

  size_t read_samples = as.read(buf, 10, 1.0f);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), read_samples);
  static const uint8_t result1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  CPPUNIT_ASSERT_EQUAL(0, memcmp(buf, result1, 10));

  read_samples = as.read(buf, 10, 1.5f);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), read_samples);
  static const uint8_t result2[] = {10, 11, 13, 14, 16, 17, 19, 20, 22, 23};
  CPPUNIT_ASSERT_EQUAL(0, memcmp(buf, result2, 10));

  read_samples = as.read(buf, 10, 0.5f);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), read_samples);
  static const uint8_t result3[] = {25, 25, 26, 26, 27, 27, 28, 28, 29, 29};
  CPPUNIT_ASSERT_EQUAL(0, memcmp(buf, result3, 10));
}

CPPUNIT_TEST_SUITE_REGISTRATION(AudioStreamTest);
