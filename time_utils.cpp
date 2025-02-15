#include "time_utils.h"
#include <cstdio>

Time parseTime(const std::string& timeStr) {
    Time t;
    sscanf(timeStr.c_str(), "%d:%d", &t.hour, &t.minute);
    return t;
}

std::string formatTime(const Time& time) {
    char buf[6];
    sprintf(buf, "%02d:%02d", time.hour, time.minute);
    return std::string(buf);
}

bool isTimeBefore(const Time& t1, const Time& t2) {
    if (t1.hour < t2.hour) {
        return true;
    } else if (t1.hour == t2.hour) {
        return t1.minute < t2.minute;
    }
    return false;
}

int timeDiffInMinutes(const Time& t1, const Time& t2) {
    return (t2.hour - t1.hour) * 60 + (t2.minute - t1.minute);
}
