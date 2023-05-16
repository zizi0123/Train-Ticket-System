#ifndef BPT_USER_H
#define BPT_USER_H

class User{
    char userID[21];
    char password[31];
    char name[21];
    char mail[31];
    int privilege;
    int ticket_pos; //车票信息记录的开始地址
};

#endif //BPT_USER_H
