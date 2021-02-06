
set(SOURCES 
	googleauth.cpp
        authwindow.cpp
)
set(HEADERS 
	googleauth.h
        authwindow.h
)

add_library(auth ${SOURCES} ${HEADERS})

target_link_libraries(auth
  PRIVATE Qt5::Core Qt5::Quick Qt5::NetworkAuth)
