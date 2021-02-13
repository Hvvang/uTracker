cmake_minimum_required(VERSION 3.17.3)

set(CMAKE_CXX_STANDARD 20)
set(NAME uTracker)
#set(DCMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.15.2/lib/cmake")

#set (cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl@1.1 -DOPENSSL_LIBRARIES=/usr/local/opt/openssl@1.1/lib)
#set( OPENSSL_INCLUDE_DIRS "/usr/local/opt/openssl@1.1/")
#set( PKG_CONFIG_PATH="/usr/local/opt/openssl@1.1/lib/pkgconfig")

project(${NAME} LANGUAGES CXX)

add_subdirectory(server)
add_subdirectory(client_1)

