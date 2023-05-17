#include "parser.h"

void Parser::GetNewLine() {
    std::cin.getline(line, 1000); //保证能够输入空格
}

std::string Parser::GetCommand() {

}

std::string Parser::GetStamp() {
    return timestamp;
}

void Parser::Process() {
    int num = 0;  //切片出的指令数
    int start = 0, end;
    std::vector<std::string> sections;
    for (int i = 0; i < strlen(line); ++i) {
        if (line[i] == ' ' && line[i + 1] != ' ') {
            start = i + 1;
        }
        if (line[i] != ' ' && (line[i + 1] == ' ' || i == strlen(line) - 1)) {
            ++num;
            end = i;
            std::string section(line + start, line + end);
            if (num == 1) {
                timestamp = section;
            }else if (num == 2){
                command = section;
            }else{
                sections.push_back(section);
            }
        }
    }
    if(command == "add_user"){

    }
}


