#include "train.h"

Train::Train() : all_trains("../files/train/train_index", "../files/train/train_seq"), released_trains("../files/release/released_index", "../files/release/released_seq"),
                 stations("../files/station/station_index", "../files/station/station_seq"), station_pairs("../files/pair/pair_index", "../files/pair/pair_seq"),
                 train_io("../files/train/train_information"),
                 ticket_io("../files/ticket/ticket_information"), orders("../files/order/order_index", "../files/order/order_seq"), order_io("../files/order/order_information"),
                 queue("../files/queue/queue_index", "../files/queue/queue_seq") {}

void Train::AddTrain(TrainInfo new_train) {
    std::vector<int> a = all_trains.Find(new_train.trainID);
    if (!a.empty()) {
        std::cout<<-1<<'\n';
        return ;
    }
    int pos = train_io.Write(new_train);
    all_trains.Insert(new_train.trainID, pos);
    std::cout<<0<<'\n';
    return ;
}

void Train::DeleteTrain(const std::string &ID) {
    std::vector<int> a1 = all_trains.Find(ID);
    std::vector<int> a2 = released_trains.Find(ID);
    if (a1.empty() || !a2.empty()) {
        std::cout<<-1<<'\n';
        return ;
    }
    all_trains.Erase(ID, a1[0]);
    std::cout<<0<<'\n';
}

void Train::ReleaseTrain(const std::string &ID) {
    std::vector<int> a1 = all_trains.Find(ID);
    std::vector<int> a2 = released_trains.Find(ID);
    if (a1.empty() || !a2.empty()) {
        std::cout<<-1<<'\n';
        return ;
    }
    TrainInfo train_info;
    train_io.Read(train_info, a1[0]);
    train_info.ticket_pos = ticket_io.ContinuousWrite(train_info.seat_num, train_info.running_duration *
                                                                           (train_info.station_num -
                                                                            1)); //写入车票信息，此时全为满票
    for (int i = 0; i < train_info.station_num; ++i) {
        stations.Insert(train_info.stations[i], a1[0]); //插入station->pos
        for (int j = i + 1; j < train_info.station_num; ++j) { //station_pair : station1_station2 表示在1,2两站之间有一班列车
            char a[81];
            strcpy(a, train_info.stations[i]);
            strcpy(a + strlen(a), train_info.stations[j]);
            station_pairs.Insert(a, a1[0]); //插入station_pair->pos
        }
    }
    released_trains.Insert(ID, a1[0]);
    std::cout<<0<<'\n';
}

void Train::QueryTrain(MyDate date, const std::string &ID) {
    std::vector<int> a1 = all_trains.Find(ID);
    if (a1.empty()) {
        std::cout<<-1<<'\n';
        return;
    }
    TrainInfo train_info;
    train_io.Read(train_info, a1[0]);
    std::cout << ID << ' ' << train_info.type << '\n';
    int price = 0;
    int count = date - train_info.start_date;
    int *ticket_nums = new int[train_info.station_num - 1];
    int ticket_start_pos = train_info.ticket_pos + count * (train_info.station_num - 1) * sizeof(int);
    ticket_io.ContinuousRead(train_info.station_num - 1, ticket_start_pos, ticket_nums);
    for (int i = 0; i < train_info.station_num; ++i) {
        std::cout << train_info.stations[i] << ' ';
        // 到达时间输出
        if (i == 0) {
            std::cout << "xx-xx xx:xx -> ";
        } else {
            std::cout << date + train_info.day_diff_arr[i] << ' ' << train_info.arriving_time[i] << " -> ";
        }
        // 离开时间输出
        if (i == train_info.station_num - 1) {
            std::cout << "xx-xx xx:xx ";
        } else {
            std::cout << date + train_info.day_diff_leav[i] << ' ' << train_info.leaving_time[i] << ' ';
        }
        std::cout << price << ' ';
        if (i != train_info.station_num - 1) price += train_info.prices[i];
        if (i != train_info.station_num - 1) {
            std::cout << ticket_nums[i] << '\n';
        } else {
            std::cout << 'x' << '\n';
        }
    }
    delete[]ticket_nums;
}

void Train::QueryTicket(QueryTicketInfo info) {
    char a[81];
    strcpy(a, info.start);
    strcpy(a + strlen(a), info.end);
    std::vector<int> poses = station_pairs.Find(a);
    if (poses.empty()){
        std::cout<<-1<<'\n';
        return;
    }
    int total_num = 0;//符合要求的车次总数
    TicketInfo *tickets = new TicketInfo[poses.size()];
    for (int pos: poses) { //对于每一班经过这两站的车次：
        TrainInfo train_info;
        train_io.Read(train_info, pos);
        int start, end;
        for (start = 0; start < train_info.station_num; ++start) {
            if (strcmp(train_info.stations[start], info.start) == 0) {
                break;
            }
        }
        int day_num = info.date - train_info.start_date - train_info.day_diff_leav[start];
        if (day_num >= 0 && day_num < train_info.running_duration) { //说明此车次符合条件
            int price = train_info.prices[start];
            int ava_seat = train_info.seat_num;
            for (end = start + 1; end < train_info.station_num; ++end) {
                if (!strcmp(train_info.stations[end], info.end)) {
                    price += train_info.prices[end];
                } else {
                    break;
                }
            }
            int *ticket_nums = new int[end - start];
            int ticket_start_pos =
                    train_info.ticket_pos + (day_num * (train_info.station_num - 1) + start) * sizeof(int);
            ticket_io.ContinuousRead(end - start, ticket_start_pos, ticket_nums);
            for (int k = 0; k < end - start; ++k) {
                if (ticket_nums[k] < ava_seat) ava_seat = ticket_nums[k];
            }
            delete[] ticket_nums;
            MyDate e_d = info.date + (train_info.arriving_time[end] - train_info.leaving_time[start]);
            tickets[total_num] = TicketInfo(train_info.trainID, info.date, train_info.leaving_time[start], e_d,
                                            train_info.arriving_time[end], price, ava_seat);
            ++total_num;
        }

    }
    if (info.time_first) {
        std::sort(tickets, tickets + total_num, CmpTime);
    } else {
        std::sort(tickets, tickets + total_num, CmpCost);
    }
    std::cout << total_num << '\n';
    for (int i = 0; i < total_num; ++i) {
        std::cout << tickets[i].trainID << ' ' << info.start << ' ' << tickets[i].start_date << ' '
                  << tickets[i].start_time << " -> " << info.end << ' ' << tickets[i].end_date << ' '
                  << tickets[i].end_time << ' ' << tickets[i].price << ' ' << tickets[i].ava_ticket << '\n';
    }
}

void Train::QueryTransfer(QueryTicketInfo info) {
    int best_val = INT32_MAX;
    TicketInfo ticket1, ticket2;
    char transfer_station[41];
    std::vector<int> poses1 = stations.Find(info.start);
    int price1, price2, seat1 = INT32_MAX, seat2 = INT32_MAX;
    for (auto &pos1: poses1) {
        TrainInfo train1;
        train_io.Read(train1, pos1);
        int start = 0, trans1;
        for (; start < train1.station_num; ++start) {
            if (strcmp(train1.stations[start], info.start) == 0) break;
        }
        int day_num1 = info.date - train1.start_date - train1.day_diff_leav[start];
        if (day_num1 < 0 || day_num1 >= train1.running_duration || start == train1.station_num - 1) continue;
        price1 = 0;
        for (trans1 = start + 1; trans1 < train1.station_num - 1; ++trans1) { //尝试以start后的每一站作为中转站
            price1 += train1.prices[trans1 - 1];
            char a[81];
            strcpy(a, train1.stations[trans1]);
            strcpy(a + strlen(a), info.end);
            MyDate trans_date1 =
                    info.date + (train1.day_diff_arr[trans1] - train1.day_diff_leav[start]); //从中转站下车的日期
            std::vector<int> poses2 = station_pairs.Find(a);
            if (!poses2.empty()) { //说明此站有作为中转站的可能
                int ticket_nums[101];
                int ticket_start_pos1 = train1.ticket_pos + (day_num1 * (train1.station_num - 1) + start) * sizeof(int);
                ticket_io.ContinuousRead(trans1 - start, ticket_start_pos1, ticket_nums);
                for (int k = 0; k < trans1 - start; ++k) {
                    if (ticket_nums[k] < seat1) seat1 = ticket_nums[k];
                }
                for (auto &pos2: poses2) { //遍历每个车次
                    int day_num2; //train2是第几号车
                    TrainInfo train2;
                    if (pos2 == pos1) continue; //要求两班车不同
                    train_io.Read(train2, pos2);
                    int trans2, end;
                    for (int k = 0; k < train2.station_num; ++k) {
                        if (strcmp(train1.stations[trans1], train2.stations[k]) == 0) {
                            trans2 = k;
                            break;
                        }
                    }
                    price2 = 0;
                    for (int k = trans2 + 1; k < train2.station_num; ++k) {
                        price2 += train2.prices[k - 1];
                        if (strcmp(info.end, train2.stations[k]) == 0) {
                            end = k;
                            break;
                        }
                    }
                    MyDate last_date = train2.start_date +
                                       (train2.running_duration - 1 + train2.day_diff_leav[trans2]); //从中转站出发的最后一天
                    MyDate first_date = train2.start_date + train2.day_diff_leav[trans2]; //从中转站出发的第一天
                    if (last_date < trans_date1 || (last_date == trans_date1 &&
                                                    train2.leaving_time[trans2] < train1.arriving_time[trans1]))
                        continue; //没有机会坐上这班车
                    MyDate trans_date2; //从中转站上车的日期
                    if (trans_date1 < first_date || (trans_date1 == first_date && train1.arriving_time[trans1] <=
                                                                                  train2.leaving_time[trans2])) {
                        day_num2 = 0;
                        trans_date2 = train2.start_date + train2.day_diff_leav[trans2];
                    } else {
                        if (train1.arriving_time[trans1] <= train2.leaving_time[trans2]) { //买同一天的即可
                            day_num2 = trans_date1 - train2.start_date;
                            trans_date2 = trans_date1;
                        } else { //得买后一天的
                            day_num2 = trans_date1 - train2.start_date + 1;
                            trans_date2 = trans_date1 + 1;
                        }
                    }
                    int ticket_start_pos2 =
                            train2.ticket_pos + (day_num2 * (train2.station_num - 1) + trans2) * sizeof(int);
                    ticket_io.ContinuousRead(end - trans2, ticket_start_pos2, ticket_nums);
                    for (int k = 0; k < end - trans2; ++k) {
                        if (ticket_nums[k] < seat2) seat2 = ticket_nums[k];
                    }
                    MyDate arrive_date = trans_date2 + (train2.day_diff_arr[end] - train2.day_diff_leav[trans2]);//下车日期
                    int price = price1 + price2;
                    int seat = seat1 < seat2 ? seat1 : seat2;
                    int time =
                            (arrive_date - info.date) * 1440 + (train2.arriving_time[end] - train1.leaving_time[start]);
                    if ((info.time_first && time < best_val) || (!info.time_first && price < best_val)) {
                        ticket1 = TicketInfo(train1.trainID, info.date, train1.leaving_time[start], trans_date1,
                                             train1.arriving_time[trans1], price1, seat);
                        ticket2 = TicketInfo(train2.trainID, trans_date2, train2.leaving_time[trans2], arrive_date,
                                             train2.arriving_time[end], price2, seat);
                        strcpy(transfer_station, train1.stations[trans1]);
                        if (info.time_first) {
                            best_val = time;
                        } else {
                            best_val = price;
                        }
                    }
                }
            }
        }
    }
    if (best_val == INT32_MAX) {
        std::cout << 0 << '\n';
    } else {
        std::cout << ticket1.trainID << ' ' << info.start << ' ' << ticket1.start_date << ' '
                  << ticket1.start_time << " -> " << transfer_station << ' ' << ticket1.end_date << ' '
                  << ticket1.end_time << ' ' << ticket1.price << ' ' << ticket1.ava_ticket << '\n';
        std::cout << ticket2.trainID << ' ' << transfer_station << ' ' << ticket2.start_date << ' '
                  << ticket2.start_time << " -> " << info.end << ' ' << ticket2.end_date << ' '
                  << ticket2.end_time << ' ' << ticket2.price << ' ' << ticket2.ava_ticket << '\n';
    }
}

void Train::Clean() {
    all_trains.Clean();
    released_trains.Clean();
    stations.Clean();
    station_pairs.Clean();
    orders.Clean();
    train_io.Clean();
    ticket_io.Clean();
    order_io.Clean();
}

void Train::BuyTicket(const BuyInfo &order_info) { //todo:要求user已登录！
    std::vector<int> a = released_trains.Find(MyString(order_info.trainID));
    if (a.empty()) {
        std::cout << -1 << '\n';
        return;
    }
    TrainInfo train;
    train_io.Read(train, a[0]);
    int start = -1, end = -1;
    for (int i = 0; i < train.station_num; ++i) {
        if (strcmp(train.stations[i], order_info.start) == 0) start = i;
        if (strcmp(train.stations[i], order_info.end) == 0) end = i;
    }
    if (start == -1 || end == -1 || start >= end || order_info.num > train.seat_num) {
        std::cout << -1 << '\n';
        return;
    }
    int day_num = order_info.date - train.start_date - train.day_diff_leav[start];
    if (day_num < 0 || day_num >= train.running_duration) {
        std::cout << -1 << '\n';
        return;
    }
    int price = 0;
    for (int i = start; i < end; ++i) price += train.prices[i];
    MyDate arrive_date = order_info.date + (train.day_diff_arr[end] - train.day_diff_leav[start]);
    int ticket_nums[100], seat = train.seat_num;
    int ticket_start_pos = train.ticket_pos + (day_num * (train.station_num - 1) + start) * sizeof(int);
    ticket_io.ContinuousRead(end - start, ticket_start_pos, ticket_nums);
    for (int k = 0; k < end - start; ++k) {
        if (ticket_nums[k] < seat) seat = ticket_nums[k];
    }
    OrderInfo order(1, train.trainID, order_info.start, order_info.end, train.leaving_time[start],
                    train.arriving_time[end], order_info.date, arrive_date, price, order_info.num, day_num,
                    end - start, ticket_start_pos); //新订单信息（默认为购票成功）
    if (seat >= order_info.num) { //购票成功
        int pos = order_io.Write(order);
        orders.Insert(MyString(order_info.userID), pos);
        for (int k = 0; k < end - start; ++k) ticket_nums[k] -= order.num;
        order_io.ContinuousWrite(end - start, ticket_start_pos, ticket_nums);
    } else {
        order.status = 0;
        int pos = order_io.Write(order);
        orders.Insert(MyString(order_info.userID), pos);
        queue.Insert(WaitingPair(order_info.trainID, day_num), pos); //插入排队信息
    }
}

void Train::QueryOrder(const std::string &ID) { //TODO：要求用户已经登录！
    std::vector<int> poses = orders.Find(ID);
    if (poses.empty()) {
        std::cout << -1 << '\n';
        return;
    }
    std::cout << poses.size() << '\n';
    for (int &pos: poses) {
        OrderInfo order;
        order_io.Read(order, pos);
        if (order.status == -1) {
            std::cout << "[refunded] ";
        } else if (order.status == 0) {
            std::cout << "[pending] ";
        } else {
            std::cout << "[success] ";
        }
        std::cout << order.trainID << ' ' << order.start << ' ' << order.start_d << ' ' << order.start_t << " -> "
                  << order.end << ' ' << order.end_d << ' ' << order.end_t << ' ' << order.price << ' ' << order.num
                  << '\n';
    }
}

void Train::RefundTicket(const std::string &ID, const int &num) {
    std::vector<int> poses = orders.Find(ID);
    if (poses.empty()) {
        std::cout << -1 << '\n';
        return;
    }
    OrderInfo order;
    order_io.Read(order, poses[num - 1]);
    if (order.status == -1) { //已退票！
        std::cout << -1 << '\n';
        return;
    }
    if (order.status == 0) {
        queue.Erase(WaitingPair(order.trainID, order.day_num), poses[0]);
        order.status = -1;
        order_io.Write(order, poses[num - 1]); //写入订单信息
        std::cout << 0 << '\n';
        return;
    }
    // 正式退票
    order.status == -1;
    order_io.Write(order, poses[num - 1]); //写入订单信息
    int *tickets = new int[order.station_nums];
    ticket_io.ContinuousRead(order.station_nums, order.ticket_start_pos, tickets);
    for (int i = 0; i < order.station_nums; ++i) tickets[i] += order.num;
    ticket_io.ContinuousWrite(order.station_nums, order.ticket_start_pos, tickets); //补票
    std::vector<int> pending_orders = queue.Find(WaitingPair(order.trainID, order.day_num));
    if (pending_orders.empty()) {
        std::cout << 0 << '\n';
        return;
    }
    for (int pos: pending_orders) {
        OrderInfo order;
        order_io.Read(order,pos);
        int *tickets = new int [order.station_nums] ;
        ticket_io.ContinuousRead(order.station_nums,order.ticket_start_pos,tickets);
        bool flag = true;
        for(int i = 0;i<order.station_nums;++i) {
            if(tickets[i]<order.num){
                flag = false;
                break;
            }
        }
        if(!flag) continue;
        //可以买到票了！
        for(int i = 0;i<order.station_nums;++i) {
            tickets[i] -= order.num;
        }
        ticket_io.ContinuousWrite(order.station_nums,order.ticket_start_pos,tickets);
        order.status = 1;
        order_io.Write(order,pos);
    }
}


