#include "gtest/gtest.h"
#include "LedDriver.h"

using namespace std;


class LedDriverFixture: public ::testing::Test {
    public:
        LedDriverFixture() : led_address(0xffff), led(&led_address){
        }

        void SetUp() {
        }

        void TearDown() {
        }

        unsigned short led_address;
        LedDriver led;
};



TEST_F(LedDriverFixture, LedsOffAfterCreate) {
    EXPECT_EQ(0x0000, led_address);
}

TEST_F(LedDriverFixture, TurnOnLedOne) {
    led_address = 0xffff;
    led.turn_on(1);
    EXPECT_EQ(0x0001, led_address);
}

TEST_F(LedDriverFixture, TurnOffLedOne) {
    led.turn_on(1);
    led.turn_off(1);
    EXPECT_EQ(0x0000, led_address);
}

TEST_F(LedDriverFixture, TurnOnMultipleLeds) {
    led.turn_on(9);
    led.turn_on(8);
    EXPECT_EQ(0x0180, led_address);
}

TEST_F(LedDriverFixture, TurnOffAnyLed) {
    led.turn_on(9);
    led.turn_on(8);
    led.turn_off(8);
    EXPECT_EQ(0x0100, led_address);
}

TEST_F(LedDriverFixture, TurnAllOn) {
    led.turn_all_on();
    EXPECT_EQ(0xffff, led_address);
}

TEST_F(LedDriverFixture, TurnOffAnyLed2) {
    led.turn_all_on();
    led.turn_off(8);
    EXPECT_EQ(0xff7f, led_address);
}

TEST_F(LedDriverFixture, UpperAndLowerBounds) {
    led.turn_on(1);
    led.turn_on(16);
    EXPECT_EQ(0x8001, led_address);
}

TEST_F(LedDriverFixture, OutOfBoundsTurnOnNoProblem) {
    led.turn_on(-1);
    led.turn_on(17);
    EXPECT_EQ(0x0000, led_address);
}

TEST_F(LedDriverFixture, OutOfBoundsTurnOffNoProblem) {
    led.turn_all_on();
    led.turn_off(-1);
    led.turn_off(17);
    EXPECT_EQ(0xffff, led_address);
}

TEST_F(LedDriverFixture, Is_On) {
    EXPECT_FALSE(led.is_on(11));
    led.turn_on(11);
    EXPECT_TRUE(led.is_on(11));
}

TEST_F(LedDriverFixture, Is_Off) {
    EXPECT_TRUE(led.is_off(11));
    led.turn_on(11);
    EXPECT_FALSE(led.is_off(11));
}

TEST_F(LedDriverFixture, turn_off_all) {
    led.turn_all_on();
    led.turn_all_off();
    EXPECT_EQ(0, led_address);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
