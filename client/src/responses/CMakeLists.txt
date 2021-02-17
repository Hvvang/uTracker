
set(SOURCES
        AbstractResponseHandler.cpp
        AuthorisationResponseHandler.cpp
        ProfileDataResponseHandler.cpp
        CreateWorkflowResponseHandler.cpp
        ArchiveWorkflowResponseHandler.cpp
        InviteContactResponseHandler.cpp
        GetWorkflowsResponseHandler.cpp
        EditWorkflowResponseHandler.cpp
        GetWorkflowColaborantsResponseHandler.cpp
        GetWorkflowPanelsResponseHandler.cpp
        GetPanelTasksResponseHandler.cpp
        GetTaskWorkersResponseHandler.cpp
        GetTagsResponseHandler.cpp
        )
set(HEADERS
        AbstractResponseHandler.h
        AuthorisationResponseHandler.h
        ProfileDataResponseHandler.h
        CreateWorkflowResponseHandler.h
        ArchiveWorkflowResponseHandler.h
        InviteContactResponseHandler.h
        GetWorkflowsResponseHandler.h
        EditWorkflowResponseHandler.h
        GetWorkflowColaborantsResponseHandler.h
        GetWorkflowPanelsResponseHandler.h
        GetPanelTasksResponseHandler.h
        GetTaskWorkersResponseHandler.h
        GetTagsResponseHandler.h
        )

add_library(ResponsesLib ${SOURCES} ${HEADERS})

target_link_libraries(ResponsesLib
        PRIVATE Qt5::Core Qt5::Quick Qt5::NetworkAuth)
