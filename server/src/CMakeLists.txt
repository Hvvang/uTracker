#cmake_minimum_required(VERSION 3.18.2)
cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES server.cpp)

set(HEADERS server.hpp)

add_library(liba ${SOURCES} ${HEADERS})

target_link_libraries(liba PRIVATE Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::DBus
)
