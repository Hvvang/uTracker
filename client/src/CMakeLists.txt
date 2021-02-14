
set(SOURCES 
		googleauth.cpp
                authwindow.cpp
		Client.cpp
                WorkflowsModel.cpp
                ColaborantsModel.cpp
)
set(HEADERS 
		googleauth.h
		authwindow.h
		Client.h
                WorkflowsModel.h
                ColaborantsModel.h
)

add_library(source ${SOURCES} ${HEADERS})

target_link_libraries(source
  PRIVATE Qt5::Core Qt5::Quick Qt5::NetworkAuth)
