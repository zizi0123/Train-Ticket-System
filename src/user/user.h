#ifndef BPT_USER_H
#define BPT_USER_H

#include "user_type.h"
#include "../utils/utils.h"
#include "../bpt/bpt.h"
#include "../rw_pointer/file_pointer.h"



//本类用于用户管理

class User{
private:
    bpt<MyString,int> all_users;
    bpt<MyString,int> users_logged;
    FilePointer<UserInfo> user_io;

public:
    User();

    void AddUser(const std::string &cur_ID, UserInfo &new_user);

    void Login(const std::string &userID,const std::string &password);

    void Logout(const std::string &userID);

    void QueryProfile(const std::string cur_ID,const std::string ID);

    void ModifyProfile(const ModifyInfo &modify_info);  //char message[]里是完整的修改指令。为了只读写一次user_info，把整段指令读进来。

    void Clean();

    void Exit(); //所有上线用户均下线

    int CheckLog(const std::string &userID);

};

#endif //BPT_USER_H
