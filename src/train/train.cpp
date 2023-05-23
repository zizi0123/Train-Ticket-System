#include "train.h"

TicketInfo::TicketInfo(char *ID, const MyDate &s_d, const MyTime &s_t, const MyDate &e_d,
                       const MyTime &e_t, const int &p, const int &a) : start_date(s_d), end_date(e_d), start_time(s_t),
                                                                        end_time(e_t), price(p), ava_ticket(a) {
    strcpy(trainID, ID);
}

TicketInfo &TicketInfo::operator=(const TicketInfo &other) {
    if (&other == this) return *this;
    strcpy(trainID, other.trainID);
    start_date = other.start_date;
    end_date = other.end_date;
    start_time = other.start_time;
    end_time = other.end_time;
    price = other.price;
    ava_ticket = other.ava_ticket;
}

bool CmpTime(const TicketInfo &a, const TicketInfo &b) {
    int x, y;
    x = (a.end_date - a.start_date) * 1440 + (a.end_time - a.start_time);
    y = (b.end_date - b.start_date) * 1440 + (b.end_time - b.start_time);
    if (x != y) return x < y;
    return (strcmp(a.trainID, b.trainID) < 0);
}


bool CmpCost(const TicketInfo &a, const TicketInfo &b) {
    if (a.price != b.price) return a.price < b.price;
    return (strcmp(a.trainID, b.trainID) < 0);
}


Train::Train() : all_trains("train_index", "train_seq"), released_trains("released_index", "released_seq"),
                 stations("station_index", "station_seq"), station_pairs("pair_index", "pair_seq"),
                 train_io("train_information"),
                 ticket_io("ticket_information") {}

int Train::AddTrain(TrainInfo new_train) {
    std::vector<int> a = all_trains.Find(new_train.trainID);
    if (!a.empty()) return -1;
    int pos = train_io.Write(new_train);
    all_trains.Insert(new_train.trainID, pos);
    return 0;
}

int Train::DeleteTrain(const std::string &ID) {
    std::vector<int> a1 = all_trains.Find(ID);
    std::vector<int> a2 = released_trains.Find(ID);
    if (a1.empty() || !a2.empty()) return -1;
    all_trains.Erase(ID, a1[0]);
    return 0;
}

int Train::ReleaseTrain(const std::string &ID) {
    std::vector<int> a1 = all_trains.Find(ID);
    std::vector<int> a2 = released_trains.Find(ID);
    if (a1.empty() || !a2.empty()) return -1;
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
    return 0;
}

int Train::QueryTrain(MyDate date, const std::string &ID) {
    std::vector<int> a1 = all_trains.Find(ID);
    if (a1.empty()) return -1;
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

int Train::QueryTicket(QueryTicketInfo info) {
    char a[81];
    strcpy(a, info.start);
    strcpy(a + strlen(a), info.end);
    std::vector<int> poses = station_pairs.Find(a);
    if (poses.empty()) return -1;
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
    int price1, price2, seat1, seat2;
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
                    int time = (arrive_date - info.date) * 1440 + (train2.arriving_time[end] - train1.leaving_time[start]);
                    if ((info.time_first && time < best_val) || (!info.time_first && price < best_val)) {
                        ticket1 = TicketInfo(train1.trainID, info.date, train1.leaving_time[start], trans_date1,
                                             train1.arriving_time[trans1], price1, seat);
                        ticket2 = TicketInfo(train2.trainID, trans_date2, train2.leaving_time[trans2], arrive_date,
                                             train2.arriving_time[end], price2, seat);
                        strcpy(transfer_station,train1.stations[trans1]);
                        if(info.time_first) {
                            best_val = time;
                        }else{
                            best_val = price;
                        }
                    }
                }
            }
        }
    }
    if(best_val == INT32_MAX) {
        std::cout<<0<<'\n';
    }else{
        std::cout << ticket1.trainID << ' ' << info.start << ' ' << ticket1.start_date << ' '
                  << ticket1.start_time << " -> " << transfer_station << ' ' << ticket1.end_date << ' '
                  << ticket1.end_time << ' ' << ticket1.price << ' ' << ticket1.ava_ticket << '\n';
        std::cout << ticket2.trainID << ' ' << transfer_station << ' ' << ticket2.start_date << ' '
                  << ticket2.start_time << " -> " << info.end << ' ' << ticket2.end_date << ' '
                  << ticket2.end_time << ' ' << ticket2.price << ' ' << ticket2.ava_ticket << '\n';
    }
}


