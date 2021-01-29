cmake_minimum_required(VERSION 3.17.3)

set(CMAKE_CXX_STANDARD 20)
set(NAME uTracker)
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.15.1/")

project(${NAME} LANGUAGES CXX)

add_subdirectory(server)
add_subdirectory(client)
