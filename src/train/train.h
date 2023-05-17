//
// Created by 86180 on 2023/5/16.
//

#ifndef BPT_TRAIN_H
#define BPT_TRAIN_H

#include "../bpt/bpt.h"

struct TrainInfo {
    char trainID[21];
    int station_num;
    char stations[101][41];
    int seat_num;
    int prices[100];
    int start_time; //每班车的发车时间
    int travel_times[100];
    int stop_over_times[100];
    int start_date; //开始售票的日期
    int running_duration; //总共开多少天
    char type;
};
struct QueryInfo{
    char start[41];
    char end[41];
    MyDate date;
    char priority[5];
};
class Train { //本类用于处理火车信息
    bpt<MyString, int> all_trains;
    bpt<MyString, int> released_trains;
public:
    void AddTrain(TrainInfo new_train);

    void DeleteTrain(char trainID[]);

    void ReleaseTrain(char trainID[]);

    void QueryTrain(MyDate date, char trainID[]);

    void QueryTicket(QueryInfo info);

    void QueryTransfer(QueryInfo info);

};
#endif //BPT_TRAIN_H
