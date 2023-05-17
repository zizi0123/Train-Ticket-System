#ifndef BPT_USER_H
#define BPT_USER_H

#include "../bpt/bpt.h"

struct UserInfo{
    char userID[21];
    char password[31];
    char name[21];
    char mail[31];
    int privilege;
};

class User{
private:
    bpt<MyString,int> all_users;
    bpt<MyString,int> users_logged;
public:
    void AddUser(UserInfo new_user);

    void Login(char userID[]);

    void Logout(char userID[]);

    void QueryProfile(char userID);

    void ModifyProfile(char message[]); //char message[]里是完整的修改指令。为了只读写一次user_info，把整段指令读进来。

};

#endif //BPT_USER_H
