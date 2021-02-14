
set(SOURCES
        ColaborantsModel.cpp
        KanbanModel.cpp
        TaskpanelModel.cpp
        WorkflowsModel.cpp
        )
set(HEADERS
        ColaborantsModel.h
        KanbanModel.h
        TaskpanelModel.h
        WorkflowsModel.h
        )

add_library(ModelsLib ${SOURCES} ${HEADERS})

target_link_libraries(ModelsLib
        PRIVATE Qt5::Core Qt5::Quick Qt5::NetworkAuth)
