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

    OrderInfo();
};

struct WaitingInfo{
    char trainID[21];
    MyDate date;
    int num;
    char start[41];
    char end[41];
    int order_pos;

    WaitingInfo();
};

class Order{
private:
    bpt<MyString,int> orders; //(userID,pos of file9)
    std::queue<WaitingInfo> queue;
public:
    Order();

    void BuyTicket(const OrderInfo &order_info);

    void QueryOrder(const std::string &ID);

    void RefundTicket(const std::string &ID,const int &num);

    void Clean();
};

#endif //BPT_ORDER_H
