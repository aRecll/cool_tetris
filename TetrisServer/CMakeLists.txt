cmake_minimum_required(VERSION 3.19)
project(TetrisServer LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network Sql HttpServer)

#find_path(HIREDIS_INCLUDE_DIR hiredis/hiredis.h)
#find_library(HIREDIS_LIBRARY hiredis)
include(FetchContent)


FetchContent_Declare(
  hiredis
  GIT_REPOSITORY https://github.com/redis/hiredis.git
  GIT_TAG        v1.3.0
)
FetchContent_MakeAvailable(hiredis)


qt_add_resources(TetrisServer_RESOURCES resources.qrc)
add_executable(TetrisServer
    src/main.cpp
    src/myserver.h src/myserver.cpp
    resources.qrc
    html/index.html
    ${TetrisServer_RESOURCES}
    #secure/cert.pem secure/key.pem secure/readme.txt

    
)
target_include_directories(TetrisServer PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src

)
target_link_libraries(TetrisServer PRIVATE 
    Qt6::Core 
    Qt6::Network 
    Qt6::Sql 
    Qt6::HttpServer
    hiredis
)
if(WIN32)
    target_link_libraries(TetrisServer PRIVATE ws2_32)
endif()
set_target_properties(TetrisServer PROPERTIES OUTPUT_NAME "TetrisServer")
