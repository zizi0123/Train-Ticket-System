//
// Created by 86180 on 2023/5/16.
//

#ifndef BPT_TRAIN_H
#define BPT_TRAIN_H

#include "../bpt/bpt.h"

struct StationPair{
    char start[41];
    char end[41];

    friend bool operator<(const StationPair &a,const StationPair &b);

    friend bool operator==(const StationPair &a,const StationPair &b);

    friend bool operator<=(const StationPair &a,const StationPair &b);

};

struct TrainInfo {
    char trainID[21];
    int station_num;
    char stations[101][41];
    int seat_num;
    int prices[100];
    MyTime start_time; //每班车的发车时间
    int travel_times[100];
    int stop_over_times[100];
    MyDate start_date; //开始售票的日期
    int running_duration; //总共开多少天
    char type;

    TrainInfo();
};
struct QueryTicketInfo{
    char start[41];
    char end[41];
    MyDate date;
    bool time_first;
};

//本类用于处理火车信息
class Train {
    bpt<MyString, int> all_trains;
    bpt<MyString, int> released_trains;
    bpt<StationPair,int> station_to_trains;
public:
    Train();

    void AddTrain(TrainInfo new_train);

    void DeleteTrain(const std::string &ID);

    void ReleaseTrain(const std::string &ID);

    void QueryTrain(MyDate date, const std::string &ID);

    void QueryTicket(QueryTicketInfo info);

    void QueryTransfer(QueryTicketInfo info);

    void Clean();

};
#endif //BPT_TRAIN_H
