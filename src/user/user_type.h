#ifndef USER_TYPE_H
#define USER_TYPE_H
#include <string>

struct UserInfo{
    char userID[21];
    char password[31];
    char name[21];
    char mail[31];
    int privilege;

};

struct ModifyInfo{
    std::string mail; //如果user_info的某个数据成员为空字符串/-1,表示此成员未被修改
    std::string password;
    std::string name;
    std::string cur_userID;
    std::string userID;
    int privilege;

};
#endif //USER_TYPE_H
