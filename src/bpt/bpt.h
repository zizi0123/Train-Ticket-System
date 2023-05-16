
#ifndef BPT_BPT_H
#define BPT_BPT_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstring>

const int M = 66, L = 71;
//const int M = 4, L = 4;


template<class Key, class Val>
struct pair {
    Key key;
    Val value;

    pair() = default;

    pair(Key k, Val v) : key(k), value(v) {}
};

template<class Key, class Val>
bool operator<(const pair<Key, Val> &a, const pair<Key, Val> &b);

template<class Key, class Val>
bool operator==(const pair<Key, Val> &a, const pair<Key, Val> &b);

template<class Key, class Val>
bool operator<=(const pair<Key, Val> &a, const pair<Key, Val> &b);

template<class Key, class Val>
struct tree_node {
    pair<Key, Val> data;
    int son_pos = 0; //指向儿子节点的指针

    tree_node() = default;

    tree_node(const pair<Key, Val> &_data, const int &pos);
};

template<class Key, class Val>
struct tree_block {
    bool if_bottom = true;
    int num = 0; //存了几个pair+指针的组合
    int my_pos;
    tree_node<Key, Val> contents[M + 1]; // 一串的内容

    tree_block() = default;

    tree_block(const bool &, const int &, const int &);
};


template<class Key, class Val>
struct pack {
    int pos; // block的第几个tree_node在链上
    tree_block<Key, Val> block;

    pack() = default;

    pack(const tree_block<Key, Val> &, const int &);
};

template<class Key, class Val>
pack<Key, Val>::pack(const tree_block<Key, Val> &b, const int &p) {
    block = b;
    pos = p;
}


template<class Key, class Val>
struct leaf_block {
    int num = 0; //存了几个元素
    int my_pos = 0;
    int next_pos = -1; //顺序遍历，下一个leave_block的位置. -1表示本叶节点已经是最后一个节点了。
    int last_pos = -1; //顺序遍历，上一个leave_block的位置. -1表示本叶节点已经是第一个节点了。
    pair<Key, Val> contents[L + 1];

    leaf_block() = default;

    leaf_block(const int &, const int &, const int &, const int &);

};

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


template<class Key, class Val>
class bpt {
private:

    const std::string index_file;
    std::fstream index_iof;
    const std::string seq_file;
    std::fstream seq_iof;
    int num_index;
    int num_seq;
    int root_pos;
    tree_block<Key, Val> root; // 把根放在文件的开头
//    bool if_empty;
    MyStack<pack<Key, Val>> buffer;

    int FindLeafBlock(const pair<Key, Val> &); // 为Insert和Erase服务的寻找叶子结点位置的函数

    int FindLeafBlockFind(const Key &);

    void InsertTreeNode(const pair<Key, Val> &, const int &pos); //在当前栈顶的tree_block的指定位置插入一个新的tree_node索引值
    void ModifyTreeNode(const pair<Key, Val> &); //更改当前栈顶的tree_block的指定位置tree_node的索引值
    void EraseTreeNode(); //删除当前栈顶的tree_block指定位置的tree_node
    void ClearBuffer();

public:

    bpt(const char *, const char *);

    ~bpt();

    void Insert(const Key &, const Val &);

    void Erase(const Key &, const Val &);

    void Find(const Key &);


};

class MyString {
public:

    char string[50];

    MyString() {
        string[0] = '\0';
    }

    MyString(const MyString &other) {
        int i = 0;
        while (true) {
            string[i] = other.string[i];
            if (string[i] == '\0') break;
            ++i;
        }
    }

    MyString &operator=(const MyString &other) {
        if (&other == this) return *this;
        int i = 0;
        while (true) {
            string[i] = other.string[i];
            if (string[i] == '\0') break;
            ++i;
        }
        return *this;
    }

    friend bool operator<(const MyString &a, const MyString &b) {
        int i;
        for (i = 0; a.string[i] != '\0' && b.string[i] != '\0'; ++i) {
            if (a.string[i] < b.string[i]) return true;
            if (a.string[i] > b.string[i]) return false;

        }
        // 说明前一段都相等
        return a.string[i] == '\0' && b.string[i] != '\0';
    }

    friend bool operator==(const MyString &a, const MyString &b) {
        int i;
        for (i = 0; a.string[i] != '\0' && b.string[i] != '\0'; ++i) {
            if (a.string[i] != b.string[i]) return false;
        }
        if (a.string[i] != '\0' || b.string[i] != '\0') return false;
        return true;
    }

    friend bool operator<=(const MyString &a, const MyString &b) {
        return a == b || a < b;
    }

    friend bool operator!=(const MyString &a, const MyString &b) {
        return !(a == b);
    }

    friend std::ostream &operator<<(std::ostream &os, const MyString &a) {
        os << a.string;
        return os; // TODO 在bpt.h里面写一部分的定义就会无法编译，说重复定义了函数
    }
};



#endif //BPT_BPT_H
