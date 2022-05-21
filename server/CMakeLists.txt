cmake_minimum_required(VERSION 3.17.3)

project(uTrackerServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(ProjectName server)

set (CMAKE_PREFIX_PATH "/usr/local/Cellar/qt@5/5.15.3")

add_compile_options(
    -std=c++20
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

find_package(Qt5 COMPONENTS Core Widgets Network Sql REQUIRED)

#include_directories(Source)

add_subdirectory(Source/Core)
add_subdirectory(Source/Crypto)

add_executable(${ProjectName} main.cpp)

target_compile_definitions(${ProjectName} PRIVATE SSLFile="${ProjectName}")

target_link_libraries(
    ${ProjectName}
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
    Qt5::Sql
    #server_src
        UTrackerServer::Core
        UTrackerServer::Crypto
)
