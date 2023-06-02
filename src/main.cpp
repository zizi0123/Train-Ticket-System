#include "bpt/bpt.h"
#include "user/user.h"
#include "train/train.h"
#include "parser/parser.h"

int main() {
    freopen("../Ticket 2023 下发数据/basic_3/5.in","r",stdin);
    freopen("outt","w",stdout);
    User user_system;
    Train train_system;
    Parser parser;
    while(parser.GetNewLine()){
        parser.Process();
        std::cout<<parser.timestamp<<' ';
        if(parser.command == "add_user"){
            user_system.AddUser(parser.current_ID,parser.user_info);
        }else if (parser.command == "login"){
            user_system.Login(parser.ID,parser.password);
        }else if (parser.command == "logout"){
            user_system.Logout(parser.ID);
        }else if(parser.command == "query_profile"){
            user_system.QueryProfile(parser.current_ID,parser.ID);
        }else if(parser.command == "modify_profile"){
            user_system.ModifyProfile(parser.modify_info);
        }else if(parser.command == "add_train"){
            train_system.AddTrain(parser.train_info);
        }else if (parser.command == "delete_train"){
            train_system.DeleteTrain(parser.ID);
        }else if(parser.command == "release_train"){
            train_system.ReleaseTrain(parser.ID);
        }else if(parser.command == "query_train"){
            train_system.QueryTrain(parser.day,parser.ID);
        }else if(parser.command == "query_ticket"){
            train_system.QueryTicket(parser.query_ticket_info);
        }else if (parser.command == "query_transfer"){
            train_system.QueryTransfer(parser.query_ticket_info);
        }else if (parser.command == "buy_ticket"){
            if(user_system.CheckLog(parser.buy_info.userID) == -1){
                std::cout<<-1<<'\n';
            }else{
                train_system.BuyTicket(parser.buy_info);
            }
        }else if(parser.command == "query_order"){
            if(user_system.CheckLog(parser.ID) == -1) {
                std::cout << -1 << '\n';
            }else {
                train_system.QueryOrder(parser.ID);
            }
        }else if(parser.command == "refund_ticket"){
            if(user_system.CheckLog(parser.ID) == -1) {
                std::cout << -1 << '\n';
            }else {
                train_system.RefundTicket(parser.ID, parser.num);
            }
        }else if(parser.command == "clean"){
            user_system.Clean();
            train_system.Clean();
        }else if(parser.command == "exit"){
            user_system.Exit();
        }
    }
}

