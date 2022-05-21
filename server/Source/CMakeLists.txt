cmake_minimum_required(VERSION 3.17.3)

set(CMAKE_CXX_STANDARD 20)
set(NAME server_src)
set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)

find_package(Qt5 COMPONENTS Core Widgets Network NetworkAuth Sql REQUIRED)
find_package(OpenSSL REQUIRED)

add_compile_options(
    -std=c++17
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

set(SRC
      connection.cpp
        database.cpp
        hash.cpp
        OAuth.cpp
        responses.cpp
        runnable.cpp
        server.cpp
)

set(HDR
        connection.h
        database.h
        hash.h
        OAuth.h
        responses.h
        runnable.h
        server.h
        )

add_subdirectory(Core)

add_library(${NAME} ${SRC} ${HDR})

target_link_libraries(
        ${NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Network
        Qt5::Sql
        Qt5::NetworkAuth
        OpenSSL::SSL
)
