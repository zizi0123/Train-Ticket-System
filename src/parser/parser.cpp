#include "parser.h"


bool Parser::GetNewLine() {
    std::cin.getline(line, 1000); //保证能够输入空格;
    return line[0]!='\0';
}

void Parser::Process() {
    int section_num = 0;  //切片出的指令数
    int start = 0, end;
    std::vector<std::string> sections;
    for (int i = 0; i < strlen(line); ++i) {
        if (line[i] == ' ' && line[i + 1] != ' ') {
            start = i + 1;
        }
        if (line[i] != ' ' && (line[i + 1] == ' ' || i == strlen(line) - 1)) {
            ++section_num;
            end = i;
            std::string section(line + start, line + end);
            if (section_num == 1) {
                timestamp = section;
            } else if (section_num == 2) {
                command = section;
            } else {
                sections.push_back(section);
            }
        }
    }
    if (command == "add_user") {
        for (int i = 1; i < sections.size(); i += 2) {
            if (sections[i - 1] == "-c") {
                current_ID = sections[i];
            } else if (sections[i - 1] == "-u") {
                strcpy(user_info.userID, sections[i].c_str());
            } else if (sections[i - 1] == "-p") {
                strcpy(user_info.password, sections[i].c_str());
            } else if (sections[i - 1] == "-n") {
                strcpy(user_info.name, sections[i].c_str());
            } else if (sections[i - 1] == "-m") {
                strcpy(user_info.mail, sections[i].c_str());
            } else if (sections[i - 1] == "-g") {
                user_info.privilege = atoi(sections[i].c_str());
            }
        }
    } else if (command == "login") {
        for (int i = 1; i < 4; i += 2) {
            if (sections[i - 1] == "-u") {
                ID = sections[i];
            } else if (sections[i - 1] == "-p") {
                password = sections[i];
            }
        }
    } else if (command == "logout" || command == "delete_train" || command == "release_train" ||
               command == "query_order") {
        ID = sections[1];
    } else if (command == "query_profile") {
        for (int i = 1; i < 4; i = i + 2) {
            if (sections[i - 1] == "-u") {
                ID = sections[i];
            } else if (sections[i - 1] == "-c") {
                current_ID = sections[i];
            }
        }
    } else if (command == "modify_profile") {
        modify_info.mail = ""; //如果user_info的某个数据成员为空字符串/-1,表示此成员未被修改
        modify_info.password = "";
        modify_info.name = "";
        modify_info.privilege = -1;
        for (int i = 1; i < sections.size(); i += 2) {
            if (sections[i - 1] == "-c") {
                modify_info.cur_userID = sections[i];
            } else if (sections[i - 1] == "-u") {
                modify_info.userID = sections[i];
            } else if (sections[i - 1] == "-p") {
                modify_info.password = sections[i];
            } else if (sections[i - 1] == "-n") {
                modify_info.name = sections[i];
            } else if (sections[i - 1] == "-m") {
                modify_info.mail = sections[i];
            } else if (sections[i - 1] == "-g") {
                modify_info.privilege = atoi(sections[i].c_str());
            }
        }
    } else if (command == "add_train") {
        for (int i = 1; i < sections.size(); i += 2) {
            if (sections[i - 1] == "-i") {
                strcpy(train_info.trainID, sections[i - 1].c_str());
            } else if (sections[i - 1] == "-n") {
                train_info.station_num = atoi(sections[i].c_str());
            } else if (sections[i - 1] == "-m") {
                train_info.seat_num = atoi(sections[i].c_str());
            } else if (sections[i - 1] == "-s") {
                int k = 0, startt = 0;
                for (int j = 0; j < sections[i].size(); ++j) {
                    if (j == sections[i].size() - 1 || sections[i][j + 1] == '|') {
                        strncpy(train_info.stations[k], sections[i].c_str() + startt, j - startt + 1);
                        train_info.stations[k][j - startt + 1] = '\0';
                        startt = j + 2;
                        ++k;
                    }
                }
            } else if (sections[i - 1] == "-p") {
                int k = 0, startt = 0;
                char a[10];
                for (int j = 0; j < sections[i].size(); ++j) {
                    if (j == sections[i].size() - 1 || sections[i][j + 1] == '|') {
                        strncpy(a, sections[i].c_str() + startt, j - startt + 1);
                        a[j - startt + 1] = '\0';
                        train_info.prices[k] = atoi(a);
                        startt = j + 2;
                        ++k;
                    }
                }
            } else if (sections[i - 1] == "-x") {
                train_info.start_time = MyTime(sections[i]);
            } else if (sections[i - 1] == "-t") {
                int k = 0, startt = 0;
                char a[10];
                for (int j = 0; j < sections[i].size(); ++j) {
                    if (j == sections[i].size() - 1 || sections[i][j + 1] == '|') {
                        strncpy(a, sections[i].c_str() + startt, j - startt + 1);
                        a[j - startt + 1] = '\0';
                        train_info.travel_times[k] = atoi(a);
                        startt = j + 2;
                        ++k;
                    }
                }
            } else if (sections[i - 1] == "-o") {
                if (train_info.station_num > 2) {
                    int k = 1, startt = 0; //注意：从1开始。即第二站的停顿时长为stop_over_time[1]
                    char a[10];
                    for (int j = 0; j < sections[i].size(); ++j) {
                        if (j == sections[i].size() - 1 || sections[i][j + 1] == '|') {
                            strncpy(a, sections[i].c_str() + startt, j - startt + 1);
                            a[j - startt + 1] = '\0';
                            train_info.stop_over_times[k] = atoi(a);
                            startt = j + 2;
                            ++k;
                        }
                    }
                }
            } else if (sections[i - 1] == "-d") {
                std::string a(sections[i], 0, 5);
                std::string b(sections[i], 6, 5);
                train_info.start_date = MyDate(a);
                train_info.running_duration = MyDate(b) - train_info.start_date;
            } else if (sections[i - 1] == "-y") {
                train_info.type = sections[i][0];
            }
        }
    } else if (command == "query_train") {
        for (int i = 1; i < 4; i += 2) {
            if (sections[i - 1] == "-i") {
                ID = sections[i];
            } else if (sections[i - 1] == "-d") {
                day = MyDate(sections[i]);
            }
        }
    } else if (command == "query_ticket" || command == "query_transfer") {
        for (int i = 1; i < sections.size(); i += 2) {
            if (sections[i - 1] == "-s") {
                strcpy(query_ticket_info.start, sections[i].c_str());
            } else if (sections[i - 1] == "-t") {
                strcpy(query_ticket_info.end, sections[i].c_str());
            } else if (sections[i - 1] == "-d") {
                query_ticket_info.date = MyDate(sections[i]);
            } else if (sections[i - 1] == "-p") {
                query_ticket_info.time_first = (sections[i] == "time");
            }
        }
    } else if (command == "buy_ticket") {
        for (int i = 1; i < sections.size(); i += 2) {
            if (sections[i - 1] == "-u") {
                strcpy(order_info.userID, sections[i].c_str());
            } else if (sections[i - 1] == "-i") {
                strcpy(order_info.trainID, sections[i].c_str());
            } else if (sections[i - 1] == "-d") {
                order_info.date = MyDate(sections[i]);
            } else if (sections[i - 1] == "-n") {
                order_info.num = atoi(sections[i].c_str());
            } else if (sections[i - 1] == "-f") {
                strcpy(order_info.start, sections[i].c_str());
            } else if (sections[i - 1] == "-t") {
                strcpy(order_info.end, sections[i].c_str());
            } else if (sections[i - 1] == "-q") {
                order_info.queue = (sections[i] == "true");
            }
        }
    } else if (command == "refund_ticket") {
        for (int i = 1; i < sections.size(); i += 2) {
            if (sections[i - 1] == "-u") {
                ID = sections[i];
            } else if (sections[i - 1] == "-i") {
                num = atoi(sections[i].c_str());
            }
        }
    }
}

Parser::Parser() {
    line[0] = '\0';
}


