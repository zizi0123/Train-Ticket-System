#include "utils.h"


MyString::MyString() {
    string[0] = '\0';
}

MyString::MyString(const MyString &other) {
    int i = 0;
    while (true) {
        string[i] = other.string[i];
        if (string[i] == '\0') break;
        ++i;
    }
}

MyString::MyString(const std::string &other) {
    for (int i = 0; i < other.size(); ++i) string[i] = other[i];
    string[other.size()] = '\0';
}

MyString::MyString(char a[]) {
    int i = 0;
    while (true) {
        string[i] = a[i];
        if (string[i] == '\0') break;
        ++i;
    }
}

MyString &MyString::operator=(const MyString &other) {
    if (&other == this) return *this;
    int i = 0;
    while (true) {
        string[i] = other.string[i];
        if (string[i] == '\0') break;
        ++i;
    }
    return *this;
}

bool operator<(const MyString &a, const MyString &b) {
    int i;
    for (i = 0; a.string[i] != '\0' && b.string[i] != '\0'; ++i) {
        if (a.string[i] < b.string[i]) return true;
        if (a.string[i] > b.string[i]) return false;

    }
    // 说明前一段都相等
    return a.string[i] == '\0' && b.string[i] != '\0';
}

bool operator==(const MyString &a, const MyString &b) {
    int i;
    for (i = 0; a.string[i] != '\0' && b.string[i] != '\0'; ++i) {
        if (a.string[i] != b.string[i]) return false;
    }
    if (a.string[i] != '\0' || b.string[i] != '\0') return false;
    return true;
}

bool operator<=(const MyString &a, const MyString &b) {
    return a == b || a < b;
}

bool operator!=(const MyString &a, const MyString &b) {
    return !(a == b);
}

std::ostream &operator<<(std::ostream &os, const MyString &a) {
    os << a.string;
    return os;
}


MyDate::MyDate(const std::string &str) {
    month = (str[0] - '0') * 10 + str[1] - '0';
    day = (str[3] - '0') * 10 + str[4] - '0';
}

MyDate::MyDate(const MyDate &other) {
    if (&other == this) return;
    day = other.day;
    month = other.month;
}

bool operator<(const MyDate &a, const MyDate &b) {
    if (a.month != b.month) return a.month < b.month;
    return a.day < b.day;
}

bool operator==(const MyDate &a, const MyDate &b) {
    return a.month == b.month && a.day == b.day;
}

bool operator<=(const MyDate &a, const MyDate &b) {
    return a == b || a < b;
}

int operator-(const MyDate &a, const MyDate &b) { //调用此函数时保证a>=b
    const int day_of_months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (a.month == b.month) return a.day - b.day + 1;
    int ans = 0;
    for (int i = b.month + 1; i < a.month; ++i) {
        ans += day_of_months[i];
    }
    ans += day_of_months[b.month] - b.day + 1;
    ans += a.day;
    return ans;
}

MyDate &MyDate::operator+=(const int &a) {
    const int day_of_months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    day += a;
    while (day > day_of_months[month]) {
        day -= day_of_months[month];
        ++month;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const MyDate &date) {
    if (date.month < 10) os << '0';
    os << date.month << '-';
    if (date.day < 10) os << '0';
    os << date.day;
    return os;
}

MyDate MyDate::operator+(const int &a) const {
    MyDate ans = *this;
    const int day_of_months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    ans.day += a;
    while (ans.day > day_of_months[ans.month]) {
        ans.day -= day_of_months[ans.month];
        ++ans.month;
    }
    return ans;
}


MyTime::MyTime(const std::string &str) {
    hour = (str[0] - '0') * 10 + str[1] - '0';
    minute = (str[3] - '0') * 10 + str[4] - '0';
}

MyTime::MyTime(const MyTime &other) {
    if (&other == this) return;
    hour = other.hour;
    minute = other.minute;
}

MyTime &MyTime::operator+=(const int &a) {
    minute += a;
    if (minute >= 60) {
        hour += minute / 60;
        minute = minute % 60;
    }
    return *this;
}

bool operator<(const MyTime &a, const MyTime &b) {
    if (a.hour != b.hour) return a.hour < b.hour;
    return a.minute < b.minute;
}

bool operator==(const MyTime &a, const MyTime &b) {
    return a.hour == b.hour && a.minute == b.minute;
}

bool operator<=(const MyTime &a, const MyTime &b) {
    return a == b || a < b;
}

int operator-(const MyTime &a, const MyTime &b) {
    int ans = (a.hour - b.hour) * 60 + a.minute - b.minute;
    return ans;
}

std::ostream &operator<<(std::ostream &os, const MyTime &time) {
    if (time.hour < 10) os << '0';
    os << time.hour << ':';
    if (time.minute < 10) os << '0';
    os << time.minute;
    return os;
}

