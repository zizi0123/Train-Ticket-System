#ifndef BPT_PARSER_H
#define BPT_PARSER_H

#include "string"
#include "iostream"
#include "../user/user.h"
#include "../order/order.h"
#include "../train/train.h"

class Parser {
private:
    char line[7000];
    std::string timestamp;
    std::string command;
    std::string ID;
    UserInfo user_info;
    OrderInfo order_info;
    TrainInfo train_info;
    QueryInfo query_info;

public:
    void GetNewLine();

    void Process();

//返回指令类型
    std::string GetCommand();

    std::string GetStamp();

    //返回执行指令所需的对应参数
    UserInfo AddUserPara();

    std::string UserID(); //为那些只需要一个userID参数的指令服务

    std::string ModiProPara();

    OrderInfo BuyPara();

    std::string RefundPara(int &num);

    TrainInfo AddTrainPara();

    std::string TrainID(); //为那些只需要一个trainID参数的指令服务

    std::string QueryTrainPara(MyDate &date);

    QueryInfo QueryTicketPara();
};


#endif //BPT_PARSER_H
