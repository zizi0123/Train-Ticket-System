//
// Created by 86180 on 2023/5/16.
//

#ifndef BPT_UTILS_H
#define BPT_UTILS_H

#include <iostream>
#include <cstring>





class MyString {
public:

    char string[81];

    MyString();

    MyString(const MyString &other);

    MyString(const std::string &other);

    MyString(char a[]);

    MyString &operator=(const MyString &other);

    friend bool operator<(const MyString &a, const MyString &b);

    friend bool operator==(const MyString &a, const MyString &b);

    friend bool operator<=(const MyString &a, const MyString &b);

    friend bool operator!=(const MyString &a, const MyString &b);

    friend std::ostream &operator<<(std::ostream &os, const MyString &a);
    // 在bpt.h里面写一部分的定义就会无法编译，说重复定义了函数
};

class MyDate{
public:
    int month = 0;
    int day = 0;

    explicit MyDate (const std::string &str);

    MyDate(const MyDate &other);

    MyDate() = default;

    MyDate &operator+=(const int & a);

    MyDate operator+(const int & a) const;

    friend bool operator<(const MyDate &a, const MyDate &b);

    friend bool operator==(const MyDate &a, const MyDate &b);

    friend bool operator<=(const MyDate &a, const MyDate &b);

    friend int operator-(const MyDate &a, const MyDate &b);

    friend std::ostream & operator<<(std::ostream &,const MyDate &);
};

class MyTime{
public:
    int hour = 0;
    int minute = 0;

    MyTime() = default;

    explicit MyTime (const std::string &str);

    MyTime(const MyTime &other);

    MyTime &operator+=(const int &a); //加上若干分钟

    friend bool operator<(const MyTime &a, const MyTime &b);

    friend bool operator==(const MyTime &a, const MyTime &b);

    friend bool operator<=(const MyTime &a, const MyTime &b);

    friend int operator-(const MyTime &a, const MyTime &b);

    friend std::ostream & operator<<(std::ostream &,const MyTime &);

};








#endif //BPT_UTILS_H
