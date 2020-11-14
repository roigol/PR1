cmake_minimum_required(VERSION 3.17)
project(PR1)

set(CMAKE_CXX_STANDARD 11)

add_executable(PR1 main.cpp ./src/Session.cpp ./src/Agent.cpp ./src/Graph.cpp ./src/Tree.cpp ./headers/Session.h ./headers/Agent.h ./headers/Graph.h ./headers/Tree.h ./headers/json.hpp config1.json)