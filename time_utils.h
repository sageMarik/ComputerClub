// time_utils.h
#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <string>

struct Time {
    int hour;
    int minute;
};

Time parseTime(const std::string& timeStr);

std::string formatTime(const Time& time);

bool isTimeBefore(const Time& t1, const Time& t2);

int timeDiffInMinutes(const Time& t1, const Time& t2);

#endif // TIME_UTILS_H
