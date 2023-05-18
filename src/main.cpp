#include "bpt/bpt.h"
#include "user/user.h"
#include "train/train.h"
#include "order/order.h"
#include "parser/parser.h"

int main() {
    User user_system;
    Train train_system;
    Order order_system;
    Parser parser;
    while(parser.GetNewLine()){
        if(parser.command == "add_user"){
            user_system.AddUser(parser.user_info);
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
            order_system.BuyTicket(parser.order_info);
        }else if(parser.command == "query_order"){
            order_system.QueryOrder(parser.ID);
        }else if(parser.command == "refund_ticket"){
            order_system.RefundTicket(parser.ID,parser.num);
        }else if(parser.command == "clean"){
            user_system.Clean();
            train_system.Clean();
            order_system.Clean();
        }else if(parser.command == "exit"){
            exit(0);
        }
    }
}

