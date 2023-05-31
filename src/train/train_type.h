#ifndef _TRAIN_TYPE_H
#define _TRAIN_TYPE_H

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

};
struct QueryTicketInfo {
    char start[41];
    char end[41];
    MyDate date;
    bool time_first;
};

struct TicketInfo {
    char trainID[21];
    MyDate start_date;
    MyTime start_time;
    MyDate end_date;
    MyTime end_time;
    int price;
    int ava_ticket;

    TicketInfo() = default; //默认构造函数必须放在下面有参数的构造函数上面

    TicketInfo(char *, const MyDate &, const MyTime &, const MyDate &, const MyTime &, const int &, const int &);

    TicketInfo &operator=(const TicketInfo &other);
};

bool CmpTime(const TicketInfo &a, const TicketInfo &b);


bool CmpCost(const TicketInfo &a, const TicketInfo &b);

struct BuyInfo {
    char userID[21];
    char trainID[21];
    MyDate date;
    int num;
    char start[41];
    char end[41];
    bool queue;
};

struct OrderInfo {


    int status; //1:success 0:pending -1:refunded
    char trainID[21];
    char start[41];
    char end[41];
    MyTime start_t;
    MyDate start_d;
    MyTime end_t;
    MyDate end_d;
    int price;
    int num;
    int day_num; //次订单购买的车次是第几天发的
    int station_nums; //表示此订单共经过了多少个区间
    int ticket_start_pos; //车票区间的开始地址

    OrderInfo() = default;

    OrderInfo(const int &s, const char ID[], const char startt[], const char endd[], const MyTime &s_t, const MyTime &e_t,
              const MyDate &, const MyDate &, const int &p, const int &n, const int &d, const int &st, const int &t);
};

struct WaitingInfo {
    char trainID[21];
    int day_num; //火车发出的天数
    int num; //票数
    int start; //起始站编号
    int end; //终点站编号
    int order_pos; //完整订单信息的位置

    WaitingInfo(const char ID[], const int &, const int &, const int &, const int &, const int &);
};

struct WaitingPair {
    char trainID[41];
    int day_num;

    WaitingPair() = default;

    WaitingPair(const char[], const int &);

    friend bool operator<(const WaitingPair &a, const WaitingPair &b);

    friend bool operator==(const WaitingPair &a, const WaitingPair &b);

    friend bool operator!=(const WaitingPair &a, const WaitingPair &b);

    friend bool operator<=(const WaitingPair &a, const WaitingPair &b);
};

#endif //_TRAIN_TYPE_H
