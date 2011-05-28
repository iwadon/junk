#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "smf_track.hpp"
#include <gtest/gtest.h>
#include "instrument.hpp"
#include "smf.hpp"
#include "song.hpp"

class SMFTrackTest : public ::testing::Test
{
protected:
  Song song_;
  Instrument inst_;

  void SetUp();
  void TearDown();
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

void SMFTrackTest::SetUp()
{
  song_.set_instrument(&inst_);
}

void SMFTrackTest::TearDown()
{
}

TEST_F(SMFTrackTest, is_playing)
{
  SMF smf(song_);
  SMFTrack t(smf);
  EXPECT_EQ(false, t.is_playing());
  t.setup(MTRK_00, sizeof MTRK_00 - 1);
  EXPECT_EQ(false, t.is_playing());
  t.play();
  EXPECT_EQ(true, t.is_playing());
  t.update();
  EXPECT_EQ(false, t.is_playing());
}

#ifdef SMF_TRACK_DEBUG

TEST_F(SMFTrackTest, inspect)
{
  SMF smf(song_);
  SMFTrack t(smf);
  EXPECT_EQ(std::string("#<SMFTrack NONE>"), t.inspect());
  t.setup(MTRK_01, sizeof MTRK_01 - 1);
  EXPECT_EQ(std::string("#<SMFTrack INITIALIZED>"), t.inspect());
  t.play();
  EXPECT_EQ(std::string("#<SMFTrack PLAYING>"), t.inspect());
  t.pause();
  EXPECT_EQ(std::string("#<SMFTrack PLAYING PAUSED>"), t.inspect());
  t.update();
  EXPECT_EQ(std::string("#<SMFTrack PLAYING PAUSED>"), t.inspect());
  t.resume();
  EXPECT_EQ(std::string("#<SMFTrack PLAYING>"), t.inspect());
  t.update();
  EXPECT_EQ(std::string("#<SMFTrack PLAYING>"), t.inspect());
  t.stop();
  EXPECT_EQ(std::string("#<SMFTrack STOPPED>"), t.inspect());
  t.update();
  EXPECT_EQ(std::string("#<SMFTrack STOPPED>"), t.inspect());
}

#endif // defined(SMF_TRACK_DEBUG)

TEST_F(SMFTrackTest, pause)
{
  SMF smf(song_);
  SMFTrack t(smf);
  t.setup(MTRK_00, sizeof MTRK_00 - 1);
  EXPECT_EQ(false, t.is_playing());
  EXPECT_EQ(false, t.is_paused());
  t.pause();
  EXPECT_EQ(false, t.is_playing());
  EXPECT_EQ(true, t.is_paused());
  t.update();
  EXPECT_EQ(false, t.is_playing());
  EXPECT_EQ(true, t.is_paused());
  t.play();
  EXPECT_EQ(true, t.is_playing());
  EXPECT_EQ(true, t.is_paused());
  t.update();
  EXPECT_EQ(true, t.is_playing());
  EXPECT_EQ(true, t.is_paused());
  t.resume();
  EXPECT_EQ(true, t.is_playing());
  EXPECT_EQ(false, t.is_paused());
  t.update();
  EXPECT_EQ(false, t.is_playing());
  EXPECT_EQ(false, t.is_paused());
}

TEST_F(SMFTrackTest, play)
{
  SMF smf(song_);
  SMFTrack t(smf);
  t.setup(MTRK_01, sizeof MTRK_01 - 1);
  EXPECT_EQ(false, t.is_playing());
  t.play();
  EXPECT_EQ(true, t.is_playing());
  for (int i = 0; i < 6; ++i) {
    t.update();
    EXPECT_EQ(true, t.is_playing());
  }
  t.update();
  EXPECT_EQ(false, t.is_playing());
}

TEST_F(SMFTrackTest, resume)
{
  SMF smf(song_);
  SMFTrack t(smf);
  t.setup(MTRK_00, sizeof MTRK_00 - 1);
  t.pause();
  t.play();
  t.update();
  EXPECT_EQ(true, t.is_playing());
  EXPECT_EQ(true, t.is_paused());
  t.resume();
  EXPECT_EQ(true, t.is_playing());
  EXPECT_EQ(false, t.is_paused());
  t.update();
  EXPECT_EQ(false, t.is_playing());
  EXPECT_EQ(false, t.is_paused());
}

TEST_F(SMFTrackTest, setup)
{
  SMF smf(song_);
  SMFTrack t(smf);
  EXPECT_EQ(true, t.setup(MTRK_00, sizeof MTRK_00 - 1));
  EXPECT_EQ(false, t.setup("ABCDEFG", 7));
  EXPECT_EQ(false, t.setup("ABCDEFGH", 8));
  EXPECT_EQ(false, t.setup("MTrk\x00\x00\x10\x00", 8));
}

TEST_F(SMFTrackTest, stop)
{
  SMF smf(song_);
  SMFTrack t(smf);
  t.setup(MTRK_01, sizeof MTRK_01 - 1);
  EXPECT_EQ(false, t.is_playing());
  t.play();
  EXPECT_EQ(true, t.is_playing());
  t.update();
  EXPECT_EQ(true, t.is_playing());
  t.stop();
  EXPECT_EQ(false, t.is_playing());
  t.update();
  EXPECT_EQ(false, t.is_playing());

  t.play();
  t.pause();
  t.stop();
  EXPECT_EQ(false, t.is_playing());
  EXPECT_EQ(false, t.is_paused());
}
