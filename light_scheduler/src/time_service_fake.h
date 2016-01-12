#ifndef __TIME_SERVICE_FAKE_H_
#define __TIME_SERVICE_FAKE_H_

#include "time_service.h"

class TimeServiceFake : public TimeService {
    public:
        TimeServiceFake() : tm_min(TIME_UNKNOWN), tm_wday(TIME_UNKNOWN) {
        }

        ~TimeServiceFake() {}

        void get_time(struct tm* t) {
            t->tm_min = tm_min;
            t->tm_sec = tm_sec;
            t->tm_hour = tm_hour;
            t->tm_wday = tm_wday;
        }

        void set_minute(int min) {
            tm_sec = 0;
            tm_min = min % 60;
            tm_hour = min / 60;
        }

        void set_day(int day) {
            tm_wday = day;
        }

        int tm_min;
        int tm_sec;
        int tm_hour;
        int tm_wday;
};

#endif
