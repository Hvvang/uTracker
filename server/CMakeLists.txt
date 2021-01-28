#cmake_minimum_required(VERSION 3.18.2)
cmake_minimum_required(VERSION 3.17)

project(utracker_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_compile_options(
#    -std=c++17
#    -Wall
#    -Wextra
#    -Werror
#    -Wpedantic
#)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network DBus REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network DBus REQUIRED)

add_subdirectory(src)

include_directories(src)

add_executable(utracker_server main.cpp)

target_link_libraries(utracker_server PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::DBus
        liba
)