#include "gtest/gtest.h"

#include "light_controller_spy.h"
#include "time_service_fake.h"
#include "light_scheduler.h"


class LightSchedulerFixture: public ::testing::Test {
    public:
        LightSchedulerFixture() {
            ctrl = new LightControllerSpy();
            ts = new TimeServiceFake();

            sch = new LightScheduler(ctrl, ts);
        }

        void SetUp() {
        }

        void TearDown() {
        }

        void set_fake_time(int day, int min) {
            dynamic_cast<TimeServiceFake*>(ts)->set_minute(min);
            dynamic_cast<TimeServiceFake*>(ts)->set_day(day);
        }

        void check_light_state(int id, int state) {
            EXPECT_EQ(id, dynamic_cast<LightControllerSpy*>(ctrl)->get_last_id());
            EXPECT_EQ(state, dynamic_cast<LightControllerSpy*>(ctrl)->get_last_state());
        }

        LightController* ctrl;
        TimeService* ts;
        LightScheduler* sch;
};

TEST_F(LightSchedulerFixture, LightControllerSpy_Create) {
    EXPECT_EQ(LIGHT_ID_UNKNOWN, dynamic_cast<LightControllerSpy*>(ctrl)->get_last_id());
    EXPECT_EQ(LIGHT_STATE_UNKNOWN, dynamic_cast<LightControllerSpy*>(ctrl)->get_last_state());
}

TEST_F(LightSchedulerFixture, LightControllerSpy_RememberLastLightIdControlled) {
    ctrl->on(10);
    EXPECT_EQ(10, dynamic_cast<LightControllerSpy*>(ctrl)->get_last_id());
    EXPECT_EQ(LIGHT_ON, dynamic_cast<LightControllerSpy*>(ctrl)->get_last_state());
}

TEST_F(LightSchedulerFixture, TimeServiceFake_Create) {
    tm t;
    ts->get_time(&t);
    EXPECT_EQ(TIME_UNKNOWN, t.tm_min);
    EXPECT_EQ(TIME_UNKNOWN, t.tm_wday);
}

TEST_F(LightSchedulerFixture, TimeServiceFake_Set) {
    set_fake_time(SAT, 42);
    tm t;
    ts->get_time(&t);
    EXPECT_EQ(42, t.tm_min);
    EXPECT_EQ(SAT, t.tm_wday);
}

TEST_F(LightSchedulerFixture, LightScheduller_NoScheduleNothingHappenns) {
    set_fake_time(SAT, 42);
    sch->wakeup();
    check_light_state(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST_F(LightSchedulerFixture, LightScheduller_ScheduleOnEverydayNotTimeYet) {
    sch->add_schedule_turn_on(3, EVERYDAY, 1200);
    set_fake_time(MON, 1199);
    sch->wakeup();
    check_light_state(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST_F(LightSchedulerFixture, LightScheduler_ScheduleOnEverydayItsTime) {
    sch->add_schedule_turn_on(3, EVERYDAY, 1200);
    set_fake_time(MON, 1200);
    sch->wakeup();
    check_light_state(3, LIGHT_ON);
}

TEST_F(LightSchedulerFixture, LightScheduler_ScheduleOffEverydayItsTime) {
    sch->add_schedule_turn_off(3, EVERYDAY, 1200);
    set_fake_time(MON, 1200);
    sch->wakeup();
    check_light_state(3, LIGHT_OFF);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
