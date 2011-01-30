#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "circular_buffer.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

class CircularBufferTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(CircularBufferTest);
  CPPUNIT_TEST(test_get);
  CPPUNIT_TEST(test_set);
  CPPUNIT_TEST(test_size);
  CPPUNIT_TEST(test_set_size);
  CPPUNIT_TEST(test_capacity);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_get();
  void test_set();
  void test_set_size();
  void test_size();
  void test_capacity();
};

void CircularBufferTest::test_get()
{
  CircularBuffer<8> cb(8);
  CPPUNIT_ASSERT_EQUAL(0.0f, cb.get());
}

void CircularBufferTest::test_set()
{
  CircularBuffer<4> cb(4);
  CPPUNIT_ASSERT_EQUAL(0.0f, cb.get());
  cb.set(1.0f);
  cb.next();
  CPPUNIT_ASSERT_EQUAL(0.0f, cb.get());
  cb.set(2.0f);
  cb.next();
  CPPUNIT_ASSERT_EQUAL(0.0f, cb.get());
  cb.set(3.0f);
  cb.next();
  CPPUNIT_ASSERT_EQUAL(0.0f, cb.get());
  cb.set(4.0f);
  cb.next();
  CPPUNIT_ASSERT_EQUAL(1.0f, cb.get());
  cb.set(5.0f);
  cb.next();
  CPPUNIT_ASSERT_EQUAL(2.0f, cb.get());
  cb.set(6.0f);
  cb.next();
  CPPUNIT_ASSERT_EQUAL(3.0f, cb.get());
  cb.set(7.0f);
  cb.next();
  CPPUNIT_ASSERT_EQUAL(4.0f, cb.get());
  cb.set(8.0f);
  cb.next();
  CPPUNIT_ASSERT_EQUAL(5.0f, cb.get());
  cb.next();
  CPPUNIT_ASSERT_EQUAL(6.0f, cb.get());
  cb.next();
  CPPUNIT_ASSERT_EQUAL(7.0f, cb.get());
  cb.next();
  CPPUNIT_ASSERT_EQUAL(8.0f, cb.get());
  cb.next();
}

void CircularBufferTest::test_size()
{
  CircularBuffer<256> cb(8);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(8), cb.size());
}

void CircularBufferTest::test_set_size()
{
  CircularBuffer<8> cb(8);
  cb.set_size(1);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), cb.size());
  cb.set_size(4);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), cb.size());
  cb.set_size(0);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), cb.size());
  cb.set_size(9);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(8), cb.size());
}

void CircularBufferTest::test_capacity()
{
  CircularBuffer<256> cb(8);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(256), cb.capacity());
}

CPPUNIT_TEST_SUITE_REGISTRATION(CircularBufferTest);
