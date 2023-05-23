//
// Created by 86180 on 2023/5/16.
//

#ifndef BPT_TRAIN_H
#define BPT_TRAIN_H

#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include "../bpt/bpt.h"
#include "../utils/utils.h"

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

struct BuyInfo{
    char userID[21];
    char trainID[21];
    MyDate date;
    int num;
    char start[41];
    char end[41];
    bool queue;

    BuyInfo();
};

struct OrderInfo{
    int status; //1:success 0:pending -1:refunded
    char trainID[21];
    char start[41];
    char end[41];
    MyTime start_t;
    MyDate start_d;
    MyTime end_t;
    MyDaye end_d;
    int price;
    int num;
    int day_num; //次订单购买的车次是第几天发的
    int station_nums; //表示此订单共经过了多少个区间
    int ticket_start_pos; //车票区间的开始地址

    OrderInfo() = default;

    OrderInfo(const int &s,const char ID[] ,const char start[],const char end[],const MyTime &s_t,const MyTime&e_t,const MyDate &,const MyDate &,const int &p,const int &n,const int &d,const int &st,const int &t);
};

struct WaitingInfo{
    char trainID[21];
    int day_num; //火车发出的天数
    int num; //票数
    int start; //起始站编号
    int end; //终点站编号
    int order_pos; //完整订单信息的位置

    WaitingInfo(const char ID[],const int&,const int&,const int&,const int&,const int&);
};

bool CmpTime(const TicketInfo &a,const TicketInfo &b);


bool CmpCost(const TicketInfo &a,const TicketInfo &b);

struct WaitingPair{
    char trainID[41];
    int day_num;

    WaitingPair() = default;

    WaitingPair(const char[],const int &);

    friend bool operator<(const WaitingPair &a,const WaitingPair &b);

    friend bool operator==(const WaitingPair &a,const WaitingPair &b);

    friend bool operator!=(const WaitingPair &a,const WaitingPair &b);

    friend bool operator<=(const WaitingPair &a,const WaitingPair &b);
};


//本类用于处理火车信息
class Train {
private:
    bpt<MyString, int> all_trains;
    bpt<MyString, int> released_trains;
    bpt<MyString,int> stations;
    bpt<MyString,int> station_pairs;
    bpt<MyString,int> orders; //(userID,pos of file18)
    bpt<WaitingPair,int> queue;
    FilePointer<TrainInfo> train_io;
    FilePointer<int> ticket_io;
    FilePointer<OrderInfo> order_io;
public:
    Train();

    int AddTrain(TrainInfo new_train);

    int DeleteTrain(const std::string &ID);

    int ReleaseTrain(const std::string &ID);

    int QueryTrain(MyDate date, const std::string &ID);

    int QueryTicket(QueryTicketInfo info);

    void QueryTransfer(QueryTicketInfo info);

    void BuyTicket(const BuyInfo &order_info);

    void QueryOrder(const std::string &ID);

    void RefundTicket(const std::string &ID,const int &num);

    void Clean();

};
#endif //BPT_TRAIN_H
