
#ifndef _FILE_POINTER_H
#define _FILE_POINTER_H
#include <string>
#include <fstream>
#include "../user/user_type.h"
#include "../train/train_type.h"


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

    void ContinuousWrite(const int &n,const int &pos,int *p); //连续n次从数组p中写入元素

    void ContinuousRead(const int &n,const int &pos,int *p); //连续n次读入元素到数组p中

    void Write(T& new_element,const int &pos); //在文件指定位置写入元素

    void Read(T& element,const int &pos); //将位置pos处的元素读入element;

    void Clean();

    bool empty();
};

#endif //_FILE_POINTER_H
