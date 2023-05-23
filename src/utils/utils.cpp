#include "utils.h"

template<class A>
MyStack<A>::MyStack() {
    num = 0;
}

template<class A>
void MyStack<A>::pop() {
    if (num > 0) --num;
}

template<class A>
void MyStack<A>::push(const A &a) {
    stack[num] = a;
    ++num;
}

template<class A>
A &MyStack<A>::top() {
    return stack[num - 1];
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

int operator-(const MyDate &a, const MyDate &b) {
    const int day_of_months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (a.month == b.month) return a.day - b.day;
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
    os << date.month << '-' << date.day;
    return os;
}

MyDate MyDate::operator+(const int &a) const {
    MyDate ans = *this;
    const int day_of_months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    ans.day += a;
    while (ans.day > day_of_months[month]) {
        ans.day -= day_of_months[month];
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
    if (minute > 60) {
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
    os << time.hour << ':' << time.minute;
    return os;
}

template<class T>
FilePointer<T>::FilePointer(const std::string &file_name) {
    std::ifstream in1(file_name);
    if (!in1) {  //如果没有打开成功，说明是初次使用系统，就创建这个文件
        std::ofstream out(file_name);
        out.close();
        num = 0;
        iof.open(file_name, std::fstream::in | std::fstream::out);
        return;
    } else {
        in1.close();
        iof.open(file_name, std::fstream::in | std::fstream::out);
        iof.read(reinterpret_cast<char *>(&num), sizeof(int));
    }
}

template<class T>
FilePointer<T>::~FilePointer() {
    iof.seekp(0);
    iof.write(reinterpret_cast<char *>(&num), sizeof(int));
    iof.close();
}


template<class T>
int FilePointer<T>::Write(T &new_element) {
    int pos = sizeof(int) + sizeof(T) * num;
    ++num;
    iof.seekp(pos);
    iof.write(reinterpret_cast<char *>(&new_element), sizeof(T));
    return pos;
}

template<class T>
void FilePointer<T>::Write(T &new_element, const int &pos) {
    iof.seekp(pos);
    iof.write(reinterpret_cast<char *>(&new_element), sizeof(T));
}

template<class T>
int FilePointer<T>::ContinuousWrite(T &ele, const int &n) {
    int pos = sizeof(int) + sizeof(T) * num;
    iof.seekp(pos);
    for (int i = 1; i <= n; ++i) iof.write(reinterpret_cast<char *>(&ele), sizeof(T));
    num += n;
    return pos;
}

template<class T>
void FilePointer<T>::ContinuousWrite(const int &n, const int &pos, int *p) {
    iof.seekp(pos);
    for(int i = 0;i<n;++i) iof.write(reinterpret_cast<char *>(&(p[i])),sizeof(T));
}

template<class T>
void FilePointer<T>::Read(T &element, const int &pos) {
    iof.seekg(pos);
    iof.read(reinterpret_cast<char *>(&element), sizeof(T));
}

template<class T>
void FilePointer<T>::Clean() {
    num = 0;
}

template<class T>
void FilePointer<T>::ContinuousRead(const int &n, const int &pos, int *p) {
    iof.seekg(pos);
    for (int i = 0; i < n; ++i) iof.read(reinterpret_cast<char *>(&(p[i])), sizeof(T));
}

template<class T>
bool FilePointer<T>::empty() {
    return num == 0;
}


template
class FilePointer<UserInfo>;

template
class FilePointer<TrainInfo>;

template
class FilePointer<BuyInfo>;
