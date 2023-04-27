#include <iostream>
#include "bpt.h"

template<class Key, class Val>
bool operator<(const pair<Key, Val> &a, const pair<Key, Val> &b) {
    if (a.key != b.key) return a.key < b.key;
    return a.value < b.value;
}

template<class Key, class Val>
bool operator==(const pair<Key, Val> &a, const pair<Key, Val> &b) {
    return a.key == b.key && a.value == b.value;
}

template<class Key, class Val>
bool operator<=(const pair<Key, Val> &a, const pair<Key, Val> &b) {
    return a == b || a < b;
}

template<class Key, class Val>
leaf_block<Key, Val>::leaf_block(const int &n, const int &my_p, const int &next_p) {
    next_pos = next_p;
    my_pos = my_p;
    num = n;
}

template<class Key, class Val>
tree_block<Key, Val>::tree_block(const bool &if_bot, const int &n, const int &my_p) {
    if_bottom = if_bot;
    num = n;
    my_pos = my_p;
}

template<class Key, class Val>
tree_node<Key, Val>::tree_node(const pair<Key, Val> &_data, const int &pos) {
    data = _data;
    son_pos = pos;
}

template<class Key, class Val>
bpt<Key, Val>::bpt(const char *Index_file, const char *Seq_file):index_file(Index_file),
                                                                 seq_file(Seq_file) {
    std::ifstream in1(index_file);
    if (!in1) {  //如果没有打开成功，说明是初次使用系统，就创建这两个文件
        std::ofstream out1(index_file), out2(seq_file);
        out1.close();
        out2.close();
        num_index = num_seq = 0;
        root_pos = 2 * sizeof(int);
        index_iof.open(index_file, std::fstream::in | std::fstream::out);
        seq_iof.open(seq_file, std::fstream::in | std::fstream::out); // 将两个读写指针关联上两个文件
        root.num = 0; // 完成树根初始化
        root.if_bottom = true;
        root.my_pos = root_pos;
        return;
    } else {
        in1.close();
        index_iof.open(index_file, std::fstream::in | std::fstream::out);
        index_iof.read(reinterpret_cast<char *>(&num_index), sizeof(int));
        index_iof.read(reinterpret_cast<char *>(&root_pos), sizeof(int));
        index_iof.seekg(root_pos);
        index_iof.read(reinterpret_cast<char *>(&root), sizeof(tree_block<Key, Val>)); // 读入树根
        seq_iof.open(seq_file, std::fstream::in | std::fstream::out);
        seq_iof.read(reinterpret_cast<char *>(&num_seq), sizeof(int));
//        leaf_block<Key, Val> leaf;  // debug
//        seq_iof.read(reinterpret_cast<char *>(&leaf), sizeof(leaf_block<Key, Val>));  //debug

    }
}

template<class Key, class Val>
bpt<Key, Val>::~bpt() {
    index_iof.seekp(0);
    index_iof.write(reinterpret_cast<char *>(&num_index), sizeof(int));
    index_iof.write(reinterpret_cast<char *>(&root_pos), sizeof(int));
    index_iof.seekp(root_pos);
    index_iof.write(reinterpret_cast<char *>(&root), sizeof(tree_block<Key, Val>));
    seq_iof.seekp(0);
    seq_iof.write(reinterpret_cast<char *>(&num_seq), sizeof(int));
    seq_iof.seekg(sizeof(int));
}


template<class Key, class Val>
void bpt<Key, Val>::Insert(const Key &key, const Val &value) {
    pair<Key, Val> new_data(key, value);
    if (root.num == 0) { //空树
        num_index = 1;
        num_seq = 1;
        root.num = 1;
        root.my_pos = 2 * sizeof(int);
        root_pos = root.my_pos;
        root.contents[0].son_pos = sizeof(int);
        root.contents[0].data = new_data;
        leaf_block<Key, Val> new_leaf(1, sizeof(int), -1); //放在第一个位置
        new_leaf.contents[0] = new_data;
        seq_iof.seekp(sizeof(int));
        seq_iof.write(reinterpret_cast<char *>(&new_leaf), sizeof(leaf_block<Key, Val>));
        return;
    }
    int son_pos = FindLeafBlock(new_data); // 此时会建立一个缓存条
    leaf_block<Key, Val> leaf;
    seq_iof.seekg(son_pos);
    seq_iof.read(reinterpret_cast<char *>(&leaf), sizeof(leaf_block<Key, Val>));
    int i; // i为新节点在插入以后应该在的位置
    for (i = 0; i < leaf.num; ++i) {
        if (new_data < leaf.contents[i]) break;
    }
    if (i >= 1 && leaf.contents[i - 1] == new_data) {
        std::cout << "data existed!" << key << ' ' << value << '\n';
        buffer.clear();
        return;
    }
    for (int j = leaf.num; j >= i + 1; --j) {
        leaf.contents[j] = leaf.contents[j - 1];
    }
    leaf.contents[i] = new_data;
    leaf.num++;

    if (leaf.num == L + 1) { // 叶节点裂块
        leaf_block<Key, Val> new_leaf(L + 1 - L / 2, sizeof(leaf_block<Key, Val>) * num_seq + sizeof(int),
                                      leaf.next_pos);
        for (int j = 0; j < L + 1 - L / 2; ++j) {
            new_leaf.contents[j] = leaf.contents[L / 2 + j];
        }
        seq_iof.seekp(new_leaf.my_pos);
        seq_iof.write(reinterpret_cast<char *>(&new_leaf), sizeof(leaf_block<Key, Val>));
        ++num_seq;
        leaf.next_pos = new_leaf.my_pos;
        leaf.num = L / 2;
        seq_iof.seekp(leaf.my_pos);
        seq_iof.write(reinterpret_cast<char *>(&leaf), sizeof(leaf_block<Key, Val>));
        InsertTreeNode(new_leaf.contents[0], new_leaf.my_pos);
    } else {
        buffer.clear();
        seq_iof.seekp(leaf.my_pos);
        seq_iof.write(reinterpret_cast<char *>(&leaf), sizeof(leaf_block<Key, Val>));
    }

}


template<class Key, class Val>
void bpt<Key, Val>::Erase(const Key &key, const Val &value) {
    if(root.num == 0) return;
    pair<Key,Val> data(key,value);
    int leaf_pos = FindLeafBlock(data); // 此时会建立一个缓存条
    leaf_block<Key, Val> leaf;
    seq_iof.seekg(leaf_pos);
    seq_iof.read(reinterpret_cast<char *>(&leaf), sizeof(leaf_block<Key, Val>));
    int i; // i为新节点在插入以后应该在的位置
    for (i = 0; i < leaf.num; ++i) {
        if (data < leaf.contents[i]) break;
    }
    if(i >= 1 && leaf.contents[i-1] == data){ //找到了待删除的元素
        for(int j = i-1;j<leaf.num-1;++j) leaf.contents[j] = leaf.contents[j+1]; //挪动
        --leaf.num;
        if(leaf.num<L/2){

        }

    }else{
        return;
    }

}

template<class Key, class Val>
void bpt<Key, Val>::Find(const Key &key) {
    if (root.num == 0) { //bpt为空
        std::cout << "null\n";
        return;
    }
    int leaf_pos = FindLeafBlock(key);
    seq_iof.seekg(leaf_pos);
    leaf_block<Key, Val> block;
    seq_iof.read(reinterpret_cast<char *>(&block), sizeof(leaf_block<Key, Val>));
    bool if_find = false, first_try = true;
    while (true) {
        for (int i = 0; i < block.num; ++i) {
            if (block.contents[i].key == key) {
                std::cout << block.contents[i].value << ' ';
                if_find = true;
            }
        }
        // 可能在下一个块的块头才出现，而本块没有出现
        if ((!if_find && first_try && block.next_pos != -1) ||
            (block.contents[block.num - 1].key == key && block.next_pos != -1)) {
            seq_iof.seekg(block.next_pos);
            seq_iof.read(reinterpret_cast<char *>(&block), sizeof(leaf_block<Key, Val>));
            first_try = false;
        } else {
            break;
        }
    }
    if (!if_find) std::cout << "null";
    std::cout << '\n';
}

template<class Key, class Val>
int bpt<Key, Val>::FindLeafBlock(const pair<Key, Val> &new_data) {  // 为Insert和Erase服务的寻找叶子结点位置的函数
    buffer.clear();
    buffer.chain.push(pack<Key, Val>(root, 0));
    while (true) {
        tree_block<Key, Val> current_block = buffer.chain.top().block;
        int i = 0; //i为目标tree_node在contents中的位置
        for (i = 0; i + 1 < current_block.num; ++i) { //找到合适的位置
            if (new_data < current_block.contents[i + 1].data) break;
        }
        int son_pos = current_block.contents[i].son_pos;
        buffer.chain.top().pos = i; //标记是第几个结点的儿子
        if (current_block.if_bottom) { //已经到底部了，找到了叶子结点的位置
            return son_pos;
        }
        index_iof.seekg(son_pos);
        tree_block<Key, Val> next_block;
        index_iof.read(reinterpret_cast<char *>(&next_block), sizeof(tree_block<Key, Val>));
        buffer.chain.push(pack<Key, Val>(next_block, 0));
    }
}

template<class Key, class Val>
int bpt<Key, Val>::FindLeafBlock(const Key &key) {  // 为Find服务的寻找叶子结点位置的函数
    tree_block<Key, Val> current_block = root;
    int i, son_pos;
    while (true) {
        for (i = 0; i + 1 < current_block.num; ++i) { //找到合适的位置
            if (key <= current_block.contents[i + 1].data.key) break;
        }
        son_pos = current_block.contents[i].son_pos;
        if (current_block.if_bottom) return son_pos;
        index_iof.seekg(son_pos);
        index_iof.read(reinterpret_cast<char *>(&current_block), sizeof(tree_block<Key, Val>));
    }
}

//在index树bottom部分的tree_block中插入一个新的pair叶节点指针
template<class Key, class Val>
void bpt<Key, Val>::InsertTreeNode(const pair<Key, Val> &data, const int &pos) {
    tree_block<Key, Val> block = buffer.chain.top().block; // 需要插入一个新节点的块
    int insert_pos = buffer.chain.top().pos;
    tree_node<Key, Val> new_node(data, pos); // 待插入的新节点
    for (int i = block.num; i >= insert_pos + 2; --i) block.contents[i] = block.contents[i - 1];
    block.contents[insert_pos + 1] = new_node;
    ++block.num;
    if (block.num <= M) { //直接退出，以上的tree_block均不受影响
        index_iof.seekp(block.my_pos);
        index_iof.write(reinterpret_cast<char *>(&block), sizeof(tree_block<Key, Val>));
        if (buffer.chain.size() == 1) {
            root = block; //更新根节点
            root_pos = root.my_pos;
        }
        buffer.clear();
        return;
    }
    // 否则需要继续裂块

    tree_block<Key, Val> new_block(block.if_bottom, M + 1 - M / 2,
                                   2 * sizeof(int) + num_index * sizeof(tree_block<Key, Val>));
    for (int i = 0; i < M + 1 - M / 2; ++i) new_block.contents[i] = block.contents[M / 2 + i];
    block.num = M / 2;
    index_iof.seekp(block.my_pos);
    index_iof.write(reinterpret_cast<char *>(&block), sizeof(tree_block<Key, Val>));
    index_iof.seekp(new_block.my_pos);
    index_iof.write(reinterpret_cast<char *>(&new_block), sizeof(tree_block<Key, Val>));
    ++num_index; //又多了一个索引块
    buffer.chain.pop();
    if (buffer.chain.size() == 0) { // 说明要裂块的是根节点
        tree_block<Key, Val> new_root(false, 2, 2 * sizeof(int) + num_index * sizeof(tree_block<Key, Val>));
        new_root.contents[0] = tree_node<Key, Val>(block.contents[0].data, block.my_pos);
        new_root.contents[1] = tree_node<Key, Val>(new_block.contents[0].data, new_block.my_pos);
        root = new_root;
        root_pos = root.my_pos;
        index_iof.seekp(new_root.my_pos);
        index_iof.write(reinterpret_cast<char *>(&new_root), sizeof(tree_block<Key, Val>));
        ++num_index;
        return;
    }
    InsertTreeNode(new_block.contents[0].data, new_block.my_pos);
}



//对用到的类型进行实例化，以保证class bpt的实现被编译过了。 注意，只有当一个类模板被实例化以后，才会对这个类的实现进行编译。
//https://blog.csdn.net/mw_nice/article/details/102958242

template
class bpt<int, int>;
// 注意，key 的类型不能是std::string.string = 动态分配的char数组指针+数组长度，把一个指针写入文件是无意义的。