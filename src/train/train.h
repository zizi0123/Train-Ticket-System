//
// Created by 86180 on 2023/5/16.
//

#ifndef BPT_TRAIN_H
#define BPT_TRAIN_H

#include "../bpt/bpt.h"
#include "../utils/utils.h"
#include "algorithm"


struct TrainInfo {
    char trainID[21];
    int station_num;
    char stations[101][41];
    int seat_num;
    int prices[100];
    MyTime start_time; //每班车的发车时间
    MyTime arriving_time[100];
    MyTime leaving_time[100];
    int day_diff_arr[100];
    int day_diff_leav[100];
    MyDate start_date; //开始售票的日期
    int running_duration; //总共开多少天
    char type;
    int ticket_pos; // 票数信息开始储存的地址

//    TrainInfo();
};
struct QueryTicketInfo{
    char start[41];
    char end[41];
    MyDate date;
    bool time_first;
};

struct TicketInfo{
    char trainID[21];
    MyDate start_date;
    MyTime start_time;
    MyDate end_date;
    MyTime end_time;
    int price;
    int ava_ticket;

    TicketInfo() = default; //默认构造函数必须放在下面有参数的构造函数上面

    TicketInfo(char *,const MyDate &,const MyTime &,const MyDate &,const MyTime &,const int &,const int &);

    TicketInfo &operator = (const TicketInfo &other);
};

//struct QueryPair{
//    int num;
//    int price;
//    int time;
//};

bool CmpTime(const TicketInfo &a,const TicketInfo &b);


bool CmpCost(const TicketInfo &a,const TicketInfo &b);




//本类用于处理火车信息
class Train {
    bpt<MyString, int> all_trains;
    bpt<MyString, int> released_trains;
    bpt<MyString,int> stations;
    bpt<MyString,int> station_pairs;
    FilePointer<TrainInfo> train_io;
    FilePointer<int> ticket_io;

public:
    Train();

    int AddTrain(TrainInfo new_train);

    int DeleteTrain(const std::string &ID);

    int ReleaseTrain(const std::string &ID);

    int QueryTrain(MyDate date, const std::string &ID);

    int QueryTicket(QueryTicketInfo info);

    void QueryTransfer(QueryTicketInfo info);

    void Clean();

};
#endif //BPT_TRAIN_H
