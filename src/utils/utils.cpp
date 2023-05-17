#include "utils.h"

template<class A>
MyStack<A>::MyStack() {
    num = 0;
}

template<class A>
void MyStack<A>::pop() {
    if(num>0) --num;
}

template<class A>
void MyStack<A>::push(const A &a) {
    stack[num] = a;
    ++num;
}

template<class A>
A &MyStack<A>::top() {
    return stack[num-1];
}

template<class A>
int MyStack<A>::size() {
    return num;
}

template<class A>
bool MyStack<A>::empty() {
    return num == 0;
}

MyString::MyString() {
    string[0] = '\0';
}

MyString::MyString(const MyString &other)  {
    int i = 0;
    while (true) {
        string[i] = other.string[i];
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

bool operator<(const MyString &a, const MyString &b)  {
    int i;
    for (i = 0; a.string[i] != '\0' && b.string[i] != '\0'; ++i) {
        if (a.string[i] < b.string[i]) return true;
        if (a.string[i] > b.string[i]) return false;

    }
    // 说明前一段都相等
    return a.string[i] == '\0' && b.string[i] != '\0';
}

bool operator==(const MyString &a, const MyString &b){
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
