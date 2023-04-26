#include "bpt.h"
#include <iostream>
#include <cstring>


int main() {
//    freopen("../makedata/in","r",stdin);
//    freopen("outtt","w",stdout);
    int num;
    std::cin >> num;
    bpt<std::string,int> bpt("index_file", "seq_file");
    char x;
    std::cin.get(x);
    int find4=0;
    for (int i = 1; i <= num; ++i) {
        char *command = new char[100];
        std::cin.getline(command, 100);
        char info[10];
        int j1 = 0;
        for (; j1 < strlen(command); ++j1) {
            if (command[j1] == ' ') break;
        }
        strncpy(info, command, j1);
        info[j1] = '\0';
        if (strcmp("insert", info) == 0 || strcmp("delete", info) == 0) {
            char index[70], value[15];
            int j2 = 0;
            for (; j2 < strlen(command); ++j2) {
                if (command[j2 + j1 + 1] == ' ') break;
            }
            strncpy(index, command + j1 + 1, j2);
            index[j2] = '\0';
            strcpy(value, command + j1 + j2 + 2);
            value[strlen(command) - (j1 + j2 + 2)] = '\0';
            int int_value = atoi(value);
            if (strcmp("insert", info) == 0) {
                bpt.Insert(index, int_value);
            } else {
                bpt.Erase(index, int_value);
            }
        } else if(strcmp("find", info) == 0){
            char index[70];
            int k=j1+1;
            while(true){
                if(command[k]==' ' || command[k]=='\0' ||command[k]=='\n'){
                    strncpy(index,command+j1+1,k-j1-1);
                    index[k-j1-1] = '\0';
                    break;
                }
                k++;
            }
            bpt.Find(index);
        }
        delete[] command;
    }
}
