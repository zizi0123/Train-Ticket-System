
#ifndef BPT_BPT_H
#define BPT_BPT_H

#include <string>
#include <fstream>
#include <cstring>
#include <stack>

const int M = 4, L = 4; // todo 改成正确的值

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

    tree_node(const pair<Key,Val> & _data, const int &pos);
};

template<class Key, class Val>
struct tree_block {
    bool if_bottom = true;
    int num = 0; //存了几个pair+指针的组合
    int my_pos;
    tree_node<Key, Val> contents[M + 1]; // 一串的内容

    tree_block() = default;

    tree_block(const bool &,const int &,const int &);
};



template<class Key, class Val>
struct pack{
    int pos; // block的第几个tree_node在链上
    tree_block<Key,Val> block;

    pack(const tree_block<Key,Val> &,const int &);
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
    pair<Key, Val> contents[L + 1];

    leaf_block() = default;

    leaf_block(const int &,const int &,const int &);

    void split();
};

template<class Key, class Val>
void leaf_block<Key, Val>::split() {

}

template<class Key, class Val>
struct Buffer {
    std::stack<pack<Key, Val>> chain;
    tree_block<Key, Val> l_bro_tree;
    tree_block<Key, Val> r_bro_tree;
    leaf_block<Key, Val> l_bro_leaf;
    leaf_block<Key, Val> r_bro_leaf;

    void clear() {
        for (int i = 1; i <= chain.size(); ++i) chain.pop();
    }
};

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
    Buffer<Key, Val> buffer;

    int FindLeafBlock(const pair<Key, Val>&); // 为Insert和Erase服务的寻找叶子结点位置的函数

    int FindLeafBlock(const Key&);
    void InsertTreeNode(const pair<Key,Val> &,const int &pos);

public:

    bpt(const char *, const char *);

    ~bpt();

    void Insert(const Key &,const Val &);

    void Erase(const Key &,const Val &);

    void Find(const Key &);


};


#endif //BPT_BPT_H
