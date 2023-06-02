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
#include "train_type.h"
#include "../utils/utils.h"
#include "../rw_pointer/file_pointer.h"

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

    bool TicketPriceCmp(const int &p,const int &t,const char ID1[] ,const char ID2[] ,int &best_t,int &best_p,const char ticketID1[],const char ticketID2[]);

    bool TicketTimeCmp(const int &p,const int &t,const char ID1[] ,const char ID2[] ,int &best_t,int &best_p,const char ticketID1[],const char ticketID2[]);

public:
    Train();

    void AddTrain(TrainInfo new_train);

    void DeleteTrain(const std::string &ID);

    void ReleaseTrain(const std::string &ID);

    void QueryTrain(const MyDate &date, const std::string &ID);

    void QueryTicket(QueryTicketInfo info);

    void QueryTransfer(QueryTicketInfo info);

    void BuyTicket(const BuyInfo &order_info);

    void QueryOrder(const std::string &ID);

    void RefundTicket(const std::string &ID,const int &num);

    void Clean();


};
#endif //BPT_TRAIN_H
