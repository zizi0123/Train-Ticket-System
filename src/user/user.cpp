#include "user.h"

User::User() : all_users("user_index", "user_seq"), users_logged("logged_index", "logged_seq"),
               user_io("user_information") {}

ModifyInfo::ModifyInfo() : privilege(-1) {}

int User::AddUser(const std::string &cur_ID, UserInfo &new_user) {
    if (all_users.Empty()) { //创建第一个用户
        new_user.privilege = 10;
        int pos = user_io.Write(new_user);
        all_users.Insert(new_user.userID, pos);
    } else {
        int pri = CheckLog(cur_ID);
        std::vector<int> a = all_users.Find(new_user.userID);
        if (!a.empty() || pri == -1 || pri <= new_user.privilege) return -1;
        int pos = user_io.Write(new_user);
        all_users.Insert(new_user.userID, pos);
        return 0;
    }
}

int User::Login(const std::string &userID, const std::string &password) {
    int pri = CheckLog(userID);
    std::vector<int> a2 = all_users.Find(userID);
    if (a2.empty() || pri != -1) return -1;
    UserInfo user_info;
    user_io.Read(user_info, a2[0]);
    if (user_info.password != password) return -1;
    users_logged.Insert(userID, user_info.privilege);
    return 0;
}

int User::Logout(const std::string &userID) {
    int pri = CheckLog(userID);
    if (pri!=-1) {
        users_logged.Erase(userID, pri);
        return 0;
    }
    return -1;
}

int User::QueryProfile(const std::string cur_ID, const std::string ID) {
    int pri = CheckLog(cur_ID);
    if (pri == -1) return -1; //确保用户已登录
    std::vector<int> a2 = all_users.Find(ID);
    if (a2.empty()) return -1; //确保待查询用户存在
    UserInfo user_info;
    user_io.Read(user_info, a2[0]);
    if (pri < user_info.privilege) return -1;
    std::cout<<user_info.userID<<' '<<user_info.name<<' '<<user_info.mail<<' '<<user_info.privilege<<'\n';
    return 0;
}

int User::ModifyProfile(const ModifyInfo &modify_info) {
    int pri = CheckLog(modify_info.cur_userID);
    if (pri == -1) return -1;  //确保用户已登录
    std::vector<int> a2 = all_users.Find(modify_info.userID);
    if (a2.empty()) return -1; //确保待修改用户存在
    UserInfo user_info;
    user_io.Read(user_info, a2[0]);
    if (pri < user_info.privilege || pri<=modify_info.privilege) return -1;
    if(modify_info.privilege > 0) user_info.privilege = modify_info.privilege;
    if(!modify_info.mail.empty()) strcpy(user_info.mail,modify_info.mail.c_str()); //string的c_str()函数会在末尾补'\0'
    if(!modify_info.name.empty()) strcpy(user_info.name,modify_info.mail.c_str());
    if(!modify_info.password.empty()) strcpy(user_info.name,modify_info.password.c_str());
    user_io.Write(user_info,a2[0]);
    std::cout<<user_info.userID<<' '<<user_info.name<<' '<<user_info.mail<<' '<<user_info.privilege<<'\n';
    return 0;
}

void User::Clean() {
    all_users.Clean();
    users_logged.Clean();
    user_io.Clean();
}

void User::Exit() {
    users_logged.Clean();
}

int User::CheckLog(const std::string &userID) {
    std::vector<int> a = users_logged.Find(userID);
    if(a.empty()) return -1;
    return a[0];
}
