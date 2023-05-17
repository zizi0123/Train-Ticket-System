//
// Created by 86180 on 2023/5/16.
//

#ifndef BPT_UTILS_H
#define BPT_UTILS_H

#include "iostream"

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

    char string[50];

    MyString();

    MyString(const MyString &other);

    MyString &operator=(const MyString &other);

    friend bool operator<(const MyString &a, const MyString &b);

    friend bool operator==(const MyString &a, const MyString &b);

    friend bool operator<=(const MyString &a, const MyString &b);

    friend bool operator!=(const MyString &a, const MyString &b);

    friend std::ostream &operator<<(std::ostream &os, const MyString &a);
    // 在bpt.h里面写一部分的定义就会无法编译，说重复定义了函数
};

class MyDate{
private:
    int month;
    int day;

    friend bool operator<(const MyDate &a, const MyDate &b);

    friend bool operator>(const MyDate &a, const MyDate &b);

    friend bool operator==(const MyDate &a, const MyDate &b);

    friend bool operator<=(const MyDate &a, const MyDate &b);

    friend bool operator>=(const MyDate &a, const MyDate &b);

    friend int operator-(const MyDate &a, const MyDate &b);


};


#endif //BPT_UTILS_H
