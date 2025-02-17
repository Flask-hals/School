#ifndef TIME_H
#define TIME_H
#include <iostream>

class Time
{
public: 
    Time();

    Time(int hour, int minute, int second);
    std::string to_string(int change = 24);

    Time(std::string time_object);

    int get_hour() const;
    int get_minute() const;
    int get_second() const;

    bool is_am() const;

    Time& operator++ ();
    Time operator++ (int);

    bool operator<(const Time& rhs) const;
    bool operator>(const Time& rhs) const;
    bool operator<=(const Time& rhs) const;
    bool operator>=(const Time& rhs) const;
    bool operator==(const Time& rhs) const;
    bool operator!=(const Time& rhs) const;

    int convert_to_second() const;

    void check_value(int hour, int minute, int second);
    std::string format() const;

private:
    int hour {};
    int minute {};
    int second {};
    bool am_or_pm {is_am()};
    int change {};
};

std::ostream& operator<<(std::ostream& os, const Time& output);

#endif