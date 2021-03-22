
set(SOURCES
        ColaborantsModel.cpp
        KanbanModel.cpp
        TaskpanelModel.cpp
        WorkflowsModel.cpp
        TaskDescriptionModel.cpp
        CheckboxPropertyModel.cpp
        DailyPlanModel.cpp
        StatisticModel.cpp

        )

set(HEADERS
        ColaborantsModel.h
        KanbanModel.h
        TaskpanelModel.h
        WorkflowsModel.h
        TaskDescriptionModel.h
        CheckboxPropertyModel.h
        DailyPlanModel.h
        StatisticModel.h

        )

add_library(ModelsLib ${SOURCES} ${HEADERS})

target_link_libraries(ModelsLib
        PRIVATE Qt5::Core Qt5::Quick Qt5::NetworkAuth)
