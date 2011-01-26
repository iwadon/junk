#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "audio_stream.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "logger.hpp"

class TestAudioStream : public AudioStream
{
public:
  size_t read(void *buf, const size_t len, const float ratio);
};

class AudioStreamTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(AudioStreamTest);
  CPPUNIT_TEST(test_read);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_read();
};

size_t TestAudioStream::read(void *buf, const size_t len, const float ratio)
{
  int16_t *p = reinterpret_cast<int16_t *>(buf);
  float n = 0.0f;
  for (size_t i = 0; i < len / 2; ++i) {
    p[i] = static_cast<int16_t>(n);
    n += ratio;
  }
  return len;
}

void AudioStreamTest::test_read()
{
  int16_t buf[10];
  TestAudioStream as1;
  size_t read_size = as1.read(buf, sizeof buf, 1.0f);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(sizeof buf), read_size);
  static const int16_t result1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  CPPUNIT_ASSERT_EQUAL(0, memcmp(buf, result1, read_size));

  TestAudioStream as2;
  read_size = as2.read(buf, sizeof buf, 1.5f);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(sizeof buf), read_size);
  static const int16_t result2[10] = {0, 1, 3, 4, 6, 7, 9, 10, 12, 13};
  CPPUNIT_ASSERT_EQUAL(0, memcmp(buf, result2, read_size));

  TestAudioStream as3;
  read_size = as3.read(buf, sizeof buf, 0.5f);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(sizeof buf), read_size);
  static const int16_t result3[10] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4};
  CPPUNIT_ASSERT_EQUAL(0, memcmp(buf, result3, read_size));
}

CPPUNIT_TEST_SUITE_REGISTRATION(AudioStreamTest);
