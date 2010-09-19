#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "smf_track.hpp"

class SMFTrackTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(SMFTrackTest);
  CPPUNIT_TEST(test_is_playing);
  CPPUNIT_TEST(test_inspect);
  CPPUNIT_TEST(test_pause);
  CPPUNIT_TEST(test_play);
  CPPUNIT_TEST(test_resume);
  CPPUNIT_TEST(test_setup);
  CPPUNIT_TEST(test_stop);
  CPPUNIT_TEST(test_update);
  CPPUNIT_TEST_SUITE_END();
public:
  void test_is_playing();
  void test_inspect();
  void test_pause();
  void test_play();
  void test_resume();
  void test_setup();
  void test_stop();
  void test_update();
};

static const SMFTrack::data_type MTRK_00[] =
  "MTrk"			// chunk type
  "\x00\x00\x00\x04"		// data size
  "\x00\xff\x2f\x00";		// end of track
static const SMFTrack::data_type MTRK_01[] =
  "MTrk"			// chunk type
  "\x00\x00\x00\x1c"		// data size
  "\x01\x90\x3c\x40"		// note on
  "\x01\x80\x3c\x40"		// note off
  "\x01\x90\x3d\x40"		// note on
  "\x01\x80\x3d\x40"		// note off
  "\x01\x90\x3e\x40"		// note on
  "\x01\x80\x3e\x40"		// note off
  "\x01\xff\x2f\x00";		// end of track

void SMFTrackTest::test_is_playing()
{
  SMFTrack t;
  CPPUNIT_ASSERT_EQUAL(false, t.is_playing());
  t.setup(MTRK_00, sizeof MTRK_00);
  CPPUNIT_ASSERT_EQUAL(false, t.is_playing());
  t.play();
  CPPUNIT_ASSERT_EQUAL(true, t.is_playing());
  t.update();
  CPPUNIT_ASSERT_EQUAL(false, t.is_playing());
}

void SMFTrackTest::test_inspect()
{
  SMFTrack t;
  CPPUNIT_ASSERT_EQUAL(std::string("#<SMFTrack NONE>"), t.inspect());
  t.setup(MTRK_01, sizeof MTRK_01);
  CPPUNIT_ASSERT_EQUAL(std::string("#<SMFTrack INITIALIZED>"), t.inspect());
  t.play();
  CPPUNIT_ASSERT_EQUAL(std::string("#<SMFTrack PLAYING>"), t.inspect());
  t.pause();
  CPPUNIT_ASSERT_EQUAL(std::string("#<SMFTrack PLAYING PAUSED>"), t.inspect());
  t.update();
  CPPUNIT_ASSERT_EQUAL(std::string("#<SMFTrack PLAYING PAUSED>"), t.inspect());
  t.resume();
  CPPUNIT_ASSERT_EQUAL(std::string("#<SMFTrack PLAYING>"), t.inspect());
  t.update();
  CPPUNIT_ASSERT_EQUAL(std::string("#<SMFTrack PLAYING>"), t.inspect());
  t.stop();
  CPPUNIT_ASSERT_EQUAL(std::string("#<SMFTrack STOPPED>"), t.inspect());
  t.update();
  CPPUNIT_ASSERT_EQUAL(std::string("#<SMFTrack STOPPED>"), t.inspect());
}

void SMFTrackTest::test_pause()
{
  SMFTrack t;
  t.setup(MTRK_00, sizeof MTRK_00);
  CPPUNIT_ASSERT_EQUAL(false, t.is_playing());
  CPPUNIT_ASSERT_EQUAL(false, t.is_paused());
  t.pause();
  CPPUNIT_ASSERT_EQUAL(false, t.is_playing());
  CPPUNIT_ASSERT_EQUAL(true, t.is_paused());
  t.update();
  CPPUNIT_ASSERT_EQUAL(false, t.is_playing());
  CPPUNIT_ASSERT_EQUAL(true, t.is_paused());
  t.play();
  CPPUNIT_ASSERT_EQUAL(true, t.is_playing());
  CPPUNIT_ASSERT_EQUAL(true, t.is_paused());
  t.update();
  CPPUNIT_ASSERT_EQUAL(true, t.is_playing());
  CPPUNIT_ASSERT_EQUAL(true, t.is_paused());
  t.resume();
  CPPUNIT_ASSERT_EQUAL(true, t.is_playing());
  CPPUNIT_ASSERT_EQUAL(false, t.is_paused());
  t.update();
  CPPUNIT_ASSERT_EQUAL(false, t.is_playing());
  CPPUNIT_ASSERT_EQUAL(false, t.is_paused());
}

void SMFTrackTest::test_play()
{
  SMFTrack t;
  t.setup(MTRK_01, sizeof MTRK_01);
  CPPUNIT_ASSERT_EQUAL(false, t.is_playing());
  t.play();
  CPPUNIT_ASSERT_EQUAL(true, t.is_playing());
  for (int i = 0; i < 6; ++i) {
    t.update();
    CPPUNIT_ASSERT_EQUAL(true, t.is_playing());
  }
  t.update();
  CPPUNIT_ASSERT_EQUAL(false, t.is_playing());
}

void SMFTrackTest::test_resume()
{
  SMFTrack t;
  t.setup(MTRK_00, sizeof MTRK_00);
  t.pause();
  t.play();
  t.update();
  CPPUNIT_ASSERT_EQUAL(true, t.is_playing());
  CPPUNIT_ASSERT_EQUAL(true, t.is_paused());
  t.resume();
  CPPUNIT_ASSERT_EQUAL(true, t.is_playing());
  CPPUNIT_ASSERT_EQUAL(false, t.is_paused());
  t.update();
  CPPUNIT_ASSERT_EQUAL(false, t.is_playing());
  CPPUNIT_ASSERT_EQUAL(false, t.is_paused());
}

void SMFTrackTest::test_setup()
{
  SMFTrack t;
  CPPUNIT_ASSERT_EQUAL(true, t.setup(MTRK_00, sizeof MTRK_00));
  CPPUNIT_ASSERT_EQUAL(false, t.setup("ABCDEFG", 7));
  CPPUNIT_ASSERT_EQUAL(false, t.setup("ABCDEFGH", 8));
  CPPUNIT_ASSERT_EQUAL(false, t.setup("MTrk\x00\x00\x10\x00", 8));
}

void SMFTrackTest::test_stop()
{
  SMFTrack t;
  t.setup(MTRK_01, sizeof MTRK_01);
  CPPUNIT_ASSERT_EQUAL(false, t.is_playing());
  t.play();
  CPPUNIT_ASSERT_EQUAL(true, t.is_playing());
  t.update();
  CPPUNIT_ASSERT_EQUAL(true, t.is_playing());
  t.stop();
  CPPUNIT_ASSERT_EQUAL(false, t.is_playing());
  t.update();
  CPPUNIT_ASSERT_EQUAL(false, t.is_playing());
}

void SMFTrackTest::test_update()
{
}

CPPUNIT_TEST_SUITE_REGISTRATION(SMFTrackTest);
