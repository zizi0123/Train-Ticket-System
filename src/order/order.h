//
// Created by 86180 on 2023/5/16.
//

#ifndef BPT_ORDER_H
#define BPT_ORDER_H
#include "../utils/utils.h"
#include "../bpt/bpt.h"
#include "queue"

struct OrderInfo{
    char userID[21];
    char trainID[21];
    MyDate date;
    int num;
    char start[41];
    char end[41];
    bool queue;
};

struct WaitingInfo{
    char trainID[21];
    MyDate date;
    int num;
    char start[41];
    char end[41];
    int order_pos;
};

class Order{
private:
    bpt<MyString,int> orders; //(userID,pos of file9)
    std::queue<WaitingInfo> queue;
public:
    void BuyTicket(OrderInfo order_info);

    void QueryOrder(char userID[]);

    void RefundTicket(char userID[],int num);
};

#endif //BPT_ORDER_H
