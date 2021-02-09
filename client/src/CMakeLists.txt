
set(SOURCES 
		googleauth.cpp
        authwindow.cpp
		Client.cpp
		Router.cpp

)
set(HEADERS 
		googleauth.h
		authwindow.h
		Client.h
		Router.h
)

add_library(auth ${SOURCES} ${HEADERS})

target_link_libraries(auth
  PRIVATE Qt5::Core Qt5::Quick Qt5::NetworkAuth)
