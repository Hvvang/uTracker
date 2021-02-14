cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)
set(NAME uTracker)
set(DCMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.15.2/lib/cmake")

#set (cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl@1.1 -DOPENSSL_LIBRARIES=/usr/local/opt/openssl@1.1/lib)
#set( OPENSSL_INCLUDE_DIRS "/usr/local/opt/openssl@1.1/")
#set( PKG_CONFIG_PATH="/usr/local/opt/openssl@1.1/lib/pkgconfig")
project(utracker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(client_1)
add_subdirectory(server)

#set_target_properties(utracker PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)

