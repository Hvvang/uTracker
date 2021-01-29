
set(SOURCES 
	googleauth.cpp
)
set(HEADERS 
	googleauth.h
)

add_library(auth ${SOURCES} ${HEADERS})

target_link_libraries(auth
  PRIVATE Qt5::Core Qt5::Quick Qt5::NetworkAuth)
