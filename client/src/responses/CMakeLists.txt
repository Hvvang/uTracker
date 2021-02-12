
set(SOURCES
        AbstractResponseHandler.cpp
        AuthorisationResponseHandler.cpp
        ProfileDataResposeHandler.cpp
        )
set(HEADERS
        AbstractResponseHandler.h
        AuthorisationResponseHandler.h
        ProfileDataResposeHandler.h
        )

add_library(ResponsesLib ${SOURCES} ${HEADERS})

target_link_libraries(ResponsesLib
        PRIVATE Qt5::Core Qt5::Quick Qt5::NetworkAuth)
