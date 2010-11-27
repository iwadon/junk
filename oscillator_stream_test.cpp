#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "oscillator_stream.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class OscillatorStreamTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(OscillatorStreamTest);
  CPPUNIT_TEST(test_read);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_read();
};

void OscillatorStreamTest::test_read()
{
  int16_t buf[10];

  OscillatorStream os1;
  size_t read_samples = os1.read(buf, 10, 1.0f);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), read_samples);
  static const int16_t result1[] = {0, 32767, 0, -32767, 0, 32767, 0, -32767, 0, 32767};
  CPPUNIT_ASSERT_EQUAL(0, memcmp(buf, result1, 10));

  OscillatorStream os2;
  read_samples = os2.read(buf, 10, 1.5f);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), read_samples);
  //static const int16_t result2[] = {0, -23169, 32767, -23169, 0, 23169, -32767, 23169, 0, -23169};
  static const int16_t result2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 10; ++i) {
    fprintf(stderr, " %d", i);
    CPPUNIT_ASSERT_EQUAL(result2[i], buf[i]);
  }

  OscillatorStream os3;
  read_samples = os3.read(buf, 10, 0.5f);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), read_samples);
  static const int16_t result3[] = {0, 23169, 32767, 23169, 0, -23169, -32767, -23169, 0, 23169};
  for (int i = 0; i < 10; ++i) {
    CPPUNIT_ASSERT_EQUAL(result3[i], buf[i]);
  }
}

CPPUNIT_TEST_SUITE_REGISTRATION(OscillatorStreamTest);
