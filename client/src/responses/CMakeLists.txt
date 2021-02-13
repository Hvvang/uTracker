
set(SOURCES
        AbstractResponseHandler.cpp
        AuthorisationResponseHandler.cpp
        ProfileDataResponseHandler.cpp
        CreateWorkflowResponseHandler.cpp
        ArchiveWorkflowResponseHandler.cpp
        )
set(HEADERS
        AbstractResponseHandler.h
        AuthorisationResponseHandler.h
        ProfileDataResponseHandler.h
        CreateWorkflowResponseHandler.h
        ArchiveWorkflowResponseHandler.h
        )

add_library(ResponsesLib ${SOURCES} ${HEADERS})

target_link_libraries(ResponsesLib
        PRIVATE Qt5::Core Qt5::Quick Qt5::NetworkAuth)
