//
// Created by 86180 on 2023/5/16.
//

#ifndef BPT_UTILS_H
#define BPT_UTILS_H

#include <iostream>
#include <fstream>
#include "../user/user.h"
#include "../train/train.h"
#include "../order/order.h"
#include <cstring>

template<class A>
class MyStack {
private:
    int num;
    A stack[50];
public:
    MyStack();

    void pop();

    void push(const A &);

    A &top();

    int size();

    bool empty();

};



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

    MyDate operator+(const int & a);

    friend bool operator<(const MyDate &a, const MyDate &b);

    friend bool operator==(const MyDate &a, const MyDate &b);

    friend bool operator<=(const MyDate &a, const MyDate &b);

    friend int operator-(const MyDate &a, const MyDate &b);

    friend std::ostream & operator<<(std::ostream &,const MyDate &)
};

class MyTime{
public:
    int hour = 0;
    int minute = 0;

    explicit MyTime (const std::string &str);

    MyTime(const MyTime &other);

    MyTime() = default;

    MyTime &operator+=(const int &a); //加上若干分钟

    friend bool operator<(const MyTime &a, const MyTime &b);

    friend bool operator==(const MyTime &a, const MyTime &b);

    friend bool operator<=(const MyTime &a, const MyTime &b);

    friend int operator-(const MyTime &a, const MyTime &b);

    friend std::ostream & operator<<(std::ostream &,const MyTime &)

};

template<class T>
class FilePointer{
private:
    std::fstream iof;
    int num;  //文件中元素的个数
public:
    explicit FilePointer(const std::string &file_name);

    ~FilePointer();

    int Write(T& new_element); //在文件末尾写入一个新元素，并且返回此元素的位置

    int ContinuousWrite(T &ele,const int &n); //连续写入n次元素ele

    void ContinuousRead(const int &n,const int &pos,int *p); //连续写入n次元素ele

    void Write(T& new_element,const int &pos); //在文件指定位置写入元素

    void Read(T& element,const int &pos); //将位置pos处的元素读入element;

    void Clean();

    bool empty();
};


#endif //BPT_UTILS_H
