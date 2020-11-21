cmake_minimum_required(VERSION 3.17)
project(PR1)

set(CMAKE_CXX_STANDARD 11)

add_executable(PR1 ./src/main.cpp ./src/FiveRuleTester.cpp ./src/Tester.cpp ./src/Session.cpp ./src/Agent.cpp ./src/Graph.cpp ./src/Tree.cpp ./include/Tester.h ./include/Session.h ./include/Agent.h ./include/Graph.h ./include/Tree.h ./include/json.hpp)