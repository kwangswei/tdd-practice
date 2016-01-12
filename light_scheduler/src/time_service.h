#ifndef __TIME_SERVICE_H_
#define __TIME_SERVICE_H_

#include <ctime>
using namespace std;

/*
struct tm {
    int tm_sec;   // Seconds
    int tm_min;   // Minutes
    int tm_hour;  // Hour (0--23)
    int tm_mday;  // Day of month (1--31)
    int tm_mon;   // Month (0--11)
    int tm_year;  // Year (calendar year minus 1900)
    int tm_wday;  // Weekday (0--6; Sunday = 0)
    int tm_yday;  // Day of year (0--365)
    int tm_isdst; // 0 if daylight savings time is not in effect)

};
*/

enum {TIME_UNKNOWN=-1, SUN, MON, TUE, WED, THU, FRI, SAT};

class TimeService {
    public:
        virtual ~TimeService() {}
        virtual void get_time(struct tm* t) = 0;
    protected:
};

#endif
