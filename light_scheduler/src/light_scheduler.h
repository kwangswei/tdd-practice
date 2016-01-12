#ifndef __LIGHT_SCHEDULER_H_
#define __LIGHT_SCHEDULER_H_

#include "light_controller.h"
#include "time_service.h"

const int EVERYDAY = 7;
const int UNUSED = -1;

enum {TURN_ON, TURN_OFF};

struct Schedule {
    int id;
    int min;
    int hour;
    int event;
};

class LightScheduler {
    public:
        LightScheduler(LightController* _ctrl, TimeService* _ts) : ctrl(_ctrl), ts(_ts) {
            schedule.id = UNUSED;
        }

        void wakeup() {
            tm t;
            ts->get_time(&t);

            processEventDueNow(t, schedule);
        }

        void processEventDueNow(tm& t, Schedule& schedule) {
            if (schedule.id == UNUSED)
                return;

            if (schedule.min != t.tm_min || schedule.hour != t.tm_hour)
                return;

            operate_light(schedule);
        }

        void operate_light(Schedule& schedule) {
            if (schedule.event == TURN_ON)
                ctrl->on(schedule.id);
            else if (schedule.event == TURN_OFF)
                ctrl->off(schedule.id);
        }

        void add_schedule_turn_on(int id, int day, int min) {
            schedule_event(id, day, min, TURN_ON);
        }

        void add_schedule_turn_off(int id, int day, int min) {
            schedule_event(id, day, min, TURN_OFF);
        }

    private:
        void schedule_event(int id, int day, int min, int event) {
            schedule.id = id;
            schedule.min = min % 60;
            schedule.hour = min / 60;
            schedule.event = event;
        }

        LightController* ctrl;
        TimeService* ts;
        Schedule schedule;
};

#endif
