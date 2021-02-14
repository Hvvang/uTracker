
set(SOURCES
        AbstractResponseHandler.cpp
        AuthorisationResponseHandler.cpp
        ProfileDataResponseHandler.cpp
        CreateWorkflowResponseHandler.cpp
        ArchiveWorkflowResponseHandler.cpp
        InviteContactResponseHandler.cpp
        GetWorkflowsResponseHandler.cpp
        )
set(HEADERS
        AbstractResponseHandler.h
        AuthorisationResponseHandler.h
        ProfileDataResponseHandler.h
        CreateWorkflowResponseHandler.h
        ArchiveWorkflowResponseHandler.h
        InviteContactResponseHandler.h
        GetWorkflowsResponseHandler.h
        )

add_library(ResponsesLib ${SOURCES} ${HEADERS})

target_link_libraries(ResponsesLib
        PRIVATE Qt5::Core Qt5::Quick Qt5::NetworkAuth)
