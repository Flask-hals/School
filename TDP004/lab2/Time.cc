#include "Time.h"
#include <sstream>
#include <iomanip>
#include <string>

Time::Time(int hour, int minute, int second)
    : hour {hour}, minute {minute}, second {second}
        {
            check_value(hour, minute, second);
        }

Time::Time()
    : hour {}, minute {}, second {}
        {}

Time::Time(std::string time_object)
    : hour {}, minute {}, second {}
    {
        int temp {};
        std::stringstream ss{time_object};

        if (size(ss.str()) == 0)
        {
            ss << "00:00:00";
        }

        if (size(ss.str()) > 8)
        {
            throw std::logic_error ("Wrong format");
        }

        if (!(ss >> temp))
        {
            throw std::logic_error ("Wrong format");
        }
        check_value(temp, minute, second);
        hour = temp;

        ss.ignore(8, ':');
        if (!(ss >> temp))
        {
            throw std::logic_error ("Wrong format");
        }
        check_value(hour, temp, second);
        minute = temp;
        
        ss.ignore(8, ':');
        if (!(ss >> temp))
        {
            throw std::logic_error ("Wrong format");
        }
        check_value(hour, minute, temp);
        second = temp;
    }

void Time::check_value(int hour, int minute, int second) {
    if (hour >= 24 || hour < 0)
    { 
        throw std::logic_error ("Hours can only be between 0 and 24");
    }
    if (minute >= 60 || minute < 0)
    {
        throw std::logic_error ("Minuterna måste vara inom intervallet 0 till 60");
    }
    if (second >= 60 || second < 0)
    {
        throw std::logic_error ("Sekunderna måste vara inom intervallet 0 till 60");
    }
}

std::string Time::to_string(int change) {
    if (change == 24)
    {
        return format();
    }
    if (change == 12)
    {
        if (hour == 12)
        {
            return format() + "pm";
        }
        else if (hour < 24 && hour > 12)
        {
            hour -= 12;
            return format() + "pm";
        }
        else if (hour == 0)
        {
            hour += 12;
            return format() + "am";
        }
        
        else
        {
            return format() + "am";
        }
    }
    throw std::logic_error ("Argument to to_string can only be 12 or 24");
}

std::string Time::format() const {
    std::stringstream ss{};
        ss << std::setw(2) << std::setfill('0')
            << hour << ":" << std::setw(2) 
            << minute  << ":" << std::setw(2) 
            << second;
        return ss.str();
}

int Time::get_hour() const{
    return hour;
}

int Time::get_minute() const{
    return minute;
}

int Time::get_second() const{
    return second;
}

bool Time::is_am() const{
    if (hour < 12 && hour >= 00)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Time& Time::operator++() {
    ++second;
    if (second == 60)
    {
        ++minute;
        second = 0;
        if (minute == 60)
        {
            ++hour;
            minute = 0;
        if (hour == 24)
        {
            hour = 0;
        }
        }
    }
    return *this;
}

Time Time::operator++(int) {
    Time temp = *this;
    operator++();
    return temp;
}

bool Time::operator<(const Time& rhs) const{
    return convert_to_second() < rhs.convert_to_second();
}

bool Time::operator>(const Time& rhs) const{
    return !(*this < rhs);
}

bool Time::operator<=(const Time& rhs) const{
    return !(rhs < *this);
}

bool Time::operator>=(const Time& rhs) const{
    return !(*this < rhs);
}

bool Time::operator==(const Time& rhs) const{
    return convert_to_second() == rhs.convert_to_second();
}

bool Time::operator!=(const Time& rhs) const{
    return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& os, const Time& output){
    os << std::setw(2) << std::setfill('0') 
        << output.get_hour() << ":" << std::setw(2) 
        << output.get_minute() << ":" << std::setw(2) 
        << output.get_second();
    return os;
}

int Time::convert_to_second() const{
    int temp {second};
    temp += (hour * 3600);
    temp += (minute * 60);
    return temp;
}