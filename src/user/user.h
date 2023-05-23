#ifndef BPT_USER_H
#define BPT_USER_H

#include "../bpt/bpt.h"
#include "string"
#include "../utils/utils.h"

struct UserInfo{
    char userID[21];
    char password[31];
    char name[21];
    char mail[31];
    int privilege;

    UserInfo();
};

struct ModifyInfo{
    std::string mail; //如果user_info的某个数据成员为空字符串/-1,表示此成员未被修改
    std::string password;
    std::string name;
    std::string cur_userID;
    std::string userID;
    int privilege;

    ModifyInfo();
};

//本类用于用户管理

class User{
private:
    bpt<MyString,int> all_users;
    bpt<MyString,int> users_logged;
    FilePointer<UserInfo> user_io;

public:
    User();

    int AddUser(const std::string &cur_ID, UserInfo &new_user);

    int Login(const std::string &userID,const std::string &password);

    int Logout(const std::string &userID);

    int QueryProfile(const std::string cur_ID,const std::string ID);

    int ModifyProfile(const ModifyInfo &modify_info);  //char message[]里是完整的修改指令。为了只读写一次user_info，把整段指令读进来。

    void Clean();

    void Exit(); //所有上线用户均下线

    int CheckLog(const std::string &userID);

};

#endif //BPT_USER_H
