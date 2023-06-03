#include "user.h"

User::User() : all_users("./files/user_index", "./files/user_seq"),
               users_logged("./files/logged_index", "./files/logged_seq"),
               user_io("./files/user_information") {}


void User::AddUser(const std::string &cur_ID, UserInfo &new_user) {
    if (all_users.Empty()) { //创建第一个用户
        new_user.privilege = 10;
        int pos = user_io.Write(new_user);
        all_users.Insert(new_user.userID, pos);
        std::cout << 0 << '\n';
    } else {
        int pri = CheckLog(cur_ID);
        MyVector<int> a = all_users.Find(new_user.userID);
        if (!a.empty() || pri == -1 || pri <= new_user.privilege) {
            std::cout << -1 << '\n';
            return;
        }
        int pos = user_io.Write(new_user);
        all_users.Insert(new_user.userID, pos);
        std::cout << 0 << '\n';
    }
}

void User::Login(const std::string &userID, const std::string &password) {
    int pri = CheckLog(userID);
    MyVector<int> a2 = all_users.Find(userID);
    if (a2.empty() || pri != -1) {
        std::cout << -1 << '\n';
        return;
    }
    UserInfo user_info;
    user_io.Read(user_info, a2[0]);
    if (user_info.password != password) {
        std::cout << -1 << '\n';
        return;
    }
    users_logged.Insert(userID, user_info.privilege);
    std::cout << 0 << '\n';
}

void User::Logout(const std::string &userID) {
    int pri = CheckLog(userID);
    if (pri != -1) {
        users_logged.Erase(userID, pri);
        std::cout << 0 << '\n';
        return;
    }
    std::cout << -1 << '\n';
}

void User::QueryProfile(const std::string cur_ID, const std::string ID) {
    int pri = CheckLog(cur_ID);
    if (pri == -1) { //确保用户已登录
        std::cout << -1 << '\n';
        return;
    }
    MyVector<int> a2 = all_users.Find(ID);
    if (a2.empty()) {  //确保待查询用户存在
        std::cout << -1 << '\n';
        return;
    }
    UserInfo user_info;
    user_io.Read(user_info, a2[0]);
    if (pri <= user_info.privilege && cur_ID != ID) {
        std::cout << -1 << '\n';
        return;
    }
    std::cout << user_info.userID << ' ' << user_info.name << ' ' << user_info.mail << ' ' << user_info.privilege
              << '\n';
}

void User::ModifyProfile(const ModifyInfo &modify_info) {
    int pri = CheckLog(modify_info.cur_userID);
    if (pri == -1) {  //确保用户已登录
        std::cout << -1 << '\n';
        return;
    }
    MyVector<int> a2 = all_users.Find(modify_info.userID);
    if (a2.empty()) { //确保待修改用户存在
        std::cout << -1 << '\n';
        return;
    }
    UserInfo user_info;
    user_io.Read(user_info, a2[0]);
    if ((pri <= user_info.privilege && modify_info.cur_userID != modify_info.userID)|| pri <= modify_info.privilege) {
        std::cout << -1 << '\n';
        return;
    }
    if (modify_info.privilege > 0) user_info.privilege = modify_info.privilege;
    if (!modify_info.mail.empty()) strcpy(user_info.mail, modify_info.mail.c_str()); //string的c_str()函数会在末尾补'\0'
    if (!modify_info.name.empty()) strcpy(user_info.name, modify_info.name.c_str());
    if (!modify_info.password.empty()) strcpy(user_info.password, modify_info.password.c_str());
    user_io.Write(user_info, a2[0]);
    std::cout << user_info.userID << ' ' << user_info.name << ' ' << user_info.mail << ' ' << user_info.privilege
              << '\n';
}

void User::Clean() {
    all_users.Clean();
    users_logged.Clean();
    user_io.Clean();
}

void User::Exit() {
    users_logged.Clean();
    std::cout<<"bye\n";
}

int User::CheckLog(const std::string &userID) {
    MyVector<int> a = users_logged.Find(userID);
    if (a.empty()) return -1;
    return a[0];
}
