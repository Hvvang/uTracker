
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
        EditPanelTitleResponseHandler.cpp
        GetTaskResponseHandler.cpp
        GetPanelResponseHandler.cpp
        RenamePanelTitleResponseHandler.cpp
        GetTaskTitleUpdatingResponseHandler.cpp
        GetTaskDescriptionResponseHandler.cpp
        GetTaskUpdatingResponseHandler.cpp
        MoveTaskResponseHandler.cpp
        RemoveTaskResponseHandler.cpp
        GetWorkStatusResponseHandler.cpp
        GetTaskWorkerResponseHandler.cpp
        RemoveTaskWorkerResponseHandler.cpp
        GetTaskDoneStatusResponseHandler.cpp
        CreateDailyTaskResponseHandler.cpp
        GetDailyPlanTasksResponseHandler.cpp
        RemoveDailyPlanTaskResponseHandler.cpp
        UpdateDailyPlanTaskResponseHandler.cpp
        ResetDailyPlanResponseHandler.cpp

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
        EditPanelTitleResponseHandler.h
        GetTaskResponseHandler.h
        GetPanelResponseHandler.h
        RenamePanelTitleResponseHandler.h
        GetTaskTitleUpdatingResponseHandler.h
        GetTaskDescriptionResponseHandler.h
        GetTaskUpdatingResponseHandler.h
        MoveTaskResponseHandler.h
        RemoveTaskResponseHandler.h
        GetWorkStatusResponseHandler.h
        GetTaskWorkerResponseHandler.h
        RemoveTaskWorkerResponseHandler.h
        GetTaskDoneStatusResponseHandler.h
        CreateDailyTaskResponseHandler.h
        GetDailyPlanTasksResponseHandler.h
        RemoveDailyPlanTaskResponseHandler.h
        UpdateDailyPlanTaskResponseHandler.h
        ResetDailyPlanResponseHandler.h

        )

add_library(ResponsesLib ${SOURCES} ${HEADERS})

target_link_libraries(ResponsesLib
        PRIVATE Qt5::Core Qt5::Quick Qt5::NetworkAuth)
