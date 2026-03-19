cmake_minimum_required(VERSION 3.19)
project(TetrisServer LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Network Sql HttpServer)
set(CMAKE_AUTOMOC ON)
qt_add_resources(TetrisServer_RESOURCES resources.qrc)
add_executable(TetrisServer
    src/main.cpp
    src/myserver.h src/myserver.cpp
    resources.qrc
    html/index.html
    ${TetrisServer_RESOURCES}
    #secure/cert.pem secure/key.pem secure/readme.txt

    
)

target_link_libraries(TetrisServer PRIVATE Qt::Core Qt::Network Qt6::Sql Qt6::HttpServer)
