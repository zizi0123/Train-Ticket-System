#include "file_pointer.h"
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

template class FilePointer<OrderInfo>;

template class FilePointer<int>;//
// Created by 86180 on 2023/5/31.
//
