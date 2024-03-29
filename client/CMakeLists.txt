cmake_minimum_required(VERSION 3.5)

project(client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Core Quick Widgets NetworkAuth LinguistTools REQUIRED)

set(TS_FILES
    translations/en_AS.ts)

include_directories(src)
include_directories(src/responses)
include_directories(src/models)

add_subdirectory(src)
add_subdirectory(src/responses)
add_subdirectory(src/models)

add_executable(utracker
  main.cpp
  src/qml.qrc
  ${TS_FILES}
)


target_compile_definitions(utracker
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(utracker
  PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets Qt5::NetworkAuth source ResponsesLib ModelsLib)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
