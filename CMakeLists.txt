cmake_minimum_required(VERSION 3.22)
project(ticket_system)

set(CMAKE_CXX_STANDARD 14)

add_executable(code src/main.cpp src/bpt/bpt.cpp src/parser/parser.cpp src/rw_pointer/file_pointer.cpp src/train/train_type.cpp src/train/train.cpp src/user/user_type.cpp src/user/user.cpp src/utils/utils.cpp)
