#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "variable_length_value.hpp"

class VariableLengthValueTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(VariableLengthValueTest);
  CPPUNIT_TEST(test_data);
  CPPUNIT_TEST(test_value);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_data();
  void test_value();
};

#define ASSERT_DATA(V, D, L) {						\
    VariableLengthValue v(V);						\
    const VariableLengthValue::data_type *d;				\
    VariableLengthValue::len_type l;					\
    v.data(&d, &l);							\
    CPPUNIT_ASSERT_EQUAL(static_cast<VariableLengthValue::len_type>(L), l); \
    CPPUNIT_ASSERT(!memcmp(d, D, L));					\
  }

#define ASSERT_VALUE(D, L, V) {						\
    VariableLengthValue d(D, L);					\
    VariableLengthValue::value_type v = d.value();			\
    CPPUNIT_ASSERT_EQUAL(static_cast<VariableLengthValue::value_type>(V), v); \
    VariableLengthValue d2(D, 0);					\
    VariableLengthValue::value_type v2 = d2.value();			\
    CPPUNIT_ASSERT_EQUAL(static_cast<VariableLengthValue::value_type>(V), v2); \
  }

void VariableLengthValueTest::test_data()
{
  ASSERT_DATA(      0x00,             "\x00", 1);
  ASSERT_DATA(      0x7f,             "\x7f", 1);
  ASSERT_DATA(      0x80,         "\x81\x00", 2);
  ASSERT_DATA(    0x3fff,         "\xff\x7f", 2);
  ASSERT_DATA(    0x4000,     "\x81\x80\x00", 3);
  ASSERT_DATA(  0x1fffff,     "\xff\xff\x7f", 3);
  ASSERT_DATA(  0x200000, "\x81\x80\x80\x00", 4);
  ASSERT_DATA(0x0fffffff, "\xff\xff\xff\x7f", 4);
}

void VariableLengthValueTest::test_value()
{
  ASSERT_VALUE(            "\x00", 1,       0x00);
  ASSERT_VALUE(            "\x7f", 1,       0x7f);
  ASSERT_VALUE(        "\x81\x00", 2,       0x80);
  ASSERT_VALUE(        "\xff\x7f", 2,     0x3fff);
  ASSERT_VALUE(    "\x81\x80\x00", 3,     0x4000);
  ASSERT_VALUE(    "\xff\xff\x7f", 3,   0x1fffff);
  ASSERT_VALUE("\x81\x80\x80\x00", 4,   0x200000);
  ASSERT_VALUE("\xff\xff\xff\x7f", 4, 0x0fffffff);
}

CPPUNIT_TEST_SUITE_REGISTRATION(VariableLengthValueTest);