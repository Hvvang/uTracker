
cmake_minimum_required(VERSION 3.5)

project(utracker LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_PREFIX_PATH /home/linuxbrew/.linuxbrew/Cellar/qt/5.15.2_6/lib/cmake/)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Quick NetworkAuth LinguistTools REQUIRED)

include_directories(src)

add_subdirectory(src)

add_definitions("-DQPM_INIT\\(E\\)=E.addImportPath\\(QStringLiteral\\(\\\"qrc:/\\\"\\)\\)\\;")
include(src/material/vendor.cmake)

add_executable(utracker
        client.cpp
        src/qml.qrc
        )
target_compile_definitions(utracker
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(utracker
        PRIVATE Qt5::Core Qt5::Quick Qt5::NetworkAuth auth)

