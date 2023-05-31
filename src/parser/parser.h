#ifndef BPT_PARSER_H
#define BPT_PARSER_H

#include <string>
#include <iostream>
#include <vector>
#include "../user/user_type.h"
#include "../train/train_type.h"
#include "../utils/utils.h"

class MyDate;


class Parser {
public:

    char line[7000];
    std::string timestamp;
    std::string command;
    std::string ID;
    std::string current_ID;
    std::string password;
    MyDate day;
    UserInfo user_info;
    ModifyInfo modify_info;
    BuyInfo buy_info;
    TrainInfo train_info;
    QueryTicketInfo query_ticket_info;
    int num = 0;

    Parser();

    bool GetNewLine();

    void Process();

};


#endif //BPT_PARSER_H
