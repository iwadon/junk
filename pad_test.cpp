#include "pad.hpp"
#include <gtest/gtest.h>
  
class PadTest : public ::testing::Test
{
protected:
  DummyPad dummy_;
  HumanPad human_;
  AutoPad auto_;
  ReplayPad replay_;

  static void auto_pad_update_cb_entry_1(AutoPad *pad, void *arg)
  {
    reinterpret_cast<PadTest *>(arg)->auto_pad_update_cb_main_1(pad);
  }

  void auto_pad_update_cb_main_1(AutoPad *pad)
  {
    pad->button = 1;
  }
};

TEST_F(PadTest, type) {
  EXPECT_EQ(PAD_TYPE_DUMMY, dummy_.type);
  EXPECT_EQ(PAD_TYPE_HUMAN, human_.type);
  EXPECT_EQ(PAD_TYPE_AUTO, auto_.type);
  EXPECT_EQ(PAD_TYPE_REPLAY, replay_.type);
}

TEST_F(PadTest, analog) {
  static const PadAnalog zero = {0.0f, 0.0f};
  EXPECT_EQ(zero, dummy_.al);
  EXPECT_EQ(zero, dummy_.ar);
}

TEST_F(PadTest, button_trigger) {
  static const PadData replay_data[4] = {
    {{0.0f, 0.0f}, {0.0f, 0.0f}, 0},
    {{0.0f, 0.0f}, {0.0f, 0.0f}, 1},
    {{0.0f, 0.0f}, {0.0f, 0.0f}, 1},
    {{0.0f, 0.0f}, {0.0f, 0.0f}, 0}
  };

  replay_.set_replay_data(replay_data, 4);
  replay_.update();
  EXPECT_EQ(0u, replay_.button_on);
  EXPECT_EQ(0u, replay_.button_off);
  replay_.update();
  EXPECT_EQ(1u, replay_.button_on);
  EXPECT_EQ(0u, replay_.button_off);
  replay_.update();
  EXPECT_EQ(0u, replay_.button_on);
  EXPECT_EQ(0u, replay_.button_off);
  replay_.update();
  EXPECT_EQ(0u, replay_.button_on);
  EXPECT_EQ(1u, replay_.button_off);
  replay_.update();
  EXPECT_EQ(0u, replay_.button_on);
  EXPECT_EQ(0u, replay_.button_off);
}

TEST_F(PadTest, logging) {
  PadData log_buf[5];
  memset(log_buf, 0, sizeof log_buf);
  auto_.update_cb.set(&PadTest::auto_pad_update_cb_entry_1, this);
  auto_.set_log_buffer(log_buf, 5);
  auto_.enable_logging();
  auto_.update();
  auto_.update();
  auto_.update();
  auto_.disable_logging();
  auto_.update();
  auto_.update();
  static const PadData log_data[5] = {
    {{0.0f, 0.0f}, {0.0f, 0.0f}, 1u},
    {{0.0f, 0.0f}, {0.0f, 0.0f}, 1u},
    {{0.0f, 0.0f}, {0.0f, 0.0f}, 1u},
    {{0.0f, 0.0f}, {0.0f, 0.0f}, 0u},
    {{0.0f, 0.0f}, {0.0f, 0.0f}, 0u}
  };
  EXPECT_TRUE(memcmp(log_buf, log_data, sizeof (PadData) * 5) == 0);
}

TEST(DummyPadTest, update) {
  static const PadAnalog zero = {0.0f, 0.0f};
  DummyPad pad;
  pad.update();
  EXPECT_EQ(zero, pad.al);
  EXPECT_EQ(zero, pad.ar);
  EXPECT_EQ(0u, pad.button);
  pad.update();
  EXPECT_EQ(zero, pad.al);
  EXPECT_EQ(zero, pad.ar);
  EXPECT_EQ(0u, pad.button);
}
  
TEST(HumanPadTest, update) {
  HumanPad pad;
  pad.update();
}

class AutoPadTest : public ::testing::Test
{
protected:
  int n_;

  static void auto_pad_update_cb_entry(AutoPad *pad, void *arg)
  {
    reinterpret_cast<AutoPadTest *>(arg)->auto_pad_update_cb_main(pad);
  }

  void auto_pad_update_cb_main(AutoPad *pad)
  {
    pad->button = 1 << n_;
    ++n_;
  }

  void SetUp()
  {
    n_ = 0;
  }
};

TEST_F(AutoPadTest, update) {
  AutoPad pad;

  pad.update_cb.set(&AutoPadTest::auto_pad_update_cb_entry, this);

  pad.update();
  EXPECT_EQ(1u, pad.button);
  pad.update();
  EXPECT_EQ(2u, pad.button);
  pad.update();
  EXPECT_EQ(4u, pad.button);
  pad.update();
  EXPECT_EQ(8u, pad.button);
}

TEST(ReplayPadTest, update) {
  static const PadData replay_data[5] = {
    {{0.0f, 0.0f}, {0.0f, 0.0f}, 0},
    {{0.5f, 0.0f}, {0.0f, 0.0f}, PAD_BUTTON_A},
    {{1.0f, 0.0f}, {0.0f, 0.0f}, 0},
    {{-1.0f, 0.0f}, {0.0f, 0.0f}, PAD_BUTTON_B},
  };
  ReplayPad pad;

  ASSERT_EQ(NULL, pad.replay_data.top);
  ASSERT_EQ(NULL, pad.replay_data.bot);
  ASSERT_EQ(NULL, pad.replay_data.cur);
  pad.set_replay_data(replay_data, 4);

  pad.update();
  EXPECT_EQ(0.0f, pad.al.x);
  EXPECT_EQ(0u, pad.button);
  pad.update();
  EXPECT_EQ(0.5f, pad.al.x);
  EXPECT_EQ(PAD_BUTTON_A, pad.button);
  pad.update();
  EXPECT_EQ(1.0f, pad.al.x);
  EXPECT_EQ(0u, pad.button);
  pad.update();
  EXPECT_EQ(-1.0f, pad.al.x);
  EXPECT_EQ(PAD_BUTTON_B, pad.button);
  pad.update();
  EXPECT_EQ(0.0f, pad.al.x);
  EXPECT_EQ(0u, pad.button);
  pad.update();
  EXPECT_EQ(0.0f, pad.al.x);
  EXPECT_EQ(0u, pad.button);
}

TEST(PadDataTest, to_string) {
  PadData data = {{0.0f, 0.3333f}, {1.0f, -1.0f}, 0xfedcba98};
  EXPECT_STREQ(" 0.00  0.33  1.00 -1.00 0xfedcba98", data.to_string().c_str());
}
