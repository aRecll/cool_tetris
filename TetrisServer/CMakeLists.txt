cmake_minimum_required(VERSION 3.19)
project(TetrisServer LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Network Sql)

add_executable(TetrisServer
    src/main.cpp
    src/myserver.h src/myserver.cpp
    
)

target_link_libraries(TetrisServer PRIVATE Qt::Core Qt::Network Qt6::Sql)
