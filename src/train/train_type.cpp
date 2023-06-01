#include "train_type.h"

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
    return *this;
}

WaitingInfo::WaitingInfo(const char ID[], const int &d, const int &n, const int &s, const int &e, const int &p)
        : day_num(d), num(n), start(s), end(e), order_pos(p) {
    strcpy(trainID, ID);
}

bool CmpTime(const TicketInfo &a, const TicketInfo &b) {
    int x, y;
    x = (a.end_date - a.start_date - 1) * 1440 + (a.end_time - a.start_time);
    y = (b.end_date - b.start_date - 1) * 1440 + (b.end_time - b.start_time);
    if (x != y) return x < y;
    return (strcmp(a.trainID, b.trainID) < 0);
}

WaitingPair::WaitingPair(const char ID[], const int &num) : day_num(num) {
    strcpy(trainID, ID);
}


bool CmpCost(const TicketInfo &a, const TicketInfo &b) {
    if (a.price != b.price) return a.price < b.price;
    return (strcmp(a.trainID, b.trainID) < 0);
}

bool operator<(const WaitingPair &a, const WaitingPair &b) {
    int q = strcmp(a.trainID, b.trainID);
    if (q != 0) {
        return q < 0;
    }
    return a.day_num < b.day_num;
}

bool operator==(const WaitingPair &a, const WaitingPair &b) {
    return a.day_num == b.day_num && strcmp(a.trainID, b.trainID) == 0;
}

bool operator!=(const WaitingPair &a, const WaitingPair &b) {
    return a.day_num != b.day_num || strcmp(a.trainID, b.trainID) != 0;
}

bool operator<=(const WaitingPair &a, const WaitingPair &b) {
    return (a == b) || a < b;
}

OrderInfo::OrderInfo(const int &s, const char *ID, const char *startt, const char *endd, const MyTime &s_t,
                     const MyTime &e_t, const MyDate &s_d, const MyDate &e_d, const int &p, const int &n, const int &d,
                     const int &st, const int &t) : status(s), start_t(s_t), start_d(s_d), end_t(e_t), end_d(e_d),
                                                    price(p), num(n), day_num(d), station_nums(st),
                                                    ticket_start_pos(t) {
    strcpy(trainID, ID);
    strcpy(start, startt);
    strcpy(end, endd);
}
