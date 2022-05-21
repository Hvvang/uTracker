# CORE module

set(ModuleName Core)

set(SourceFiles
        Private/Application.cpp
        Private/ApplicationContext.cpp
        Private/Server.cpp
        Private/Core.cpp
)

set(HeaderFiles
        Public/Application.h
        Public/ApplicationContext.h
        Public/TaskInterface.h
        Public/Server.h
        Public/Core.h
)


add_library(${ModuleName} STATIC
        ${SourceFiles}
        ${HeaderFiles}
)
target_compile_definitions(${ModuleName} PRIVATE DbFile="${ProjectName}Db")

target_compile_features(${ModuleName} PUBLIC cxx_std_20)

target_include_directories(${ModuleName}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Public>
        $<INSTALL_INTERFACE:Public>
        PRIVATE
        Private
)

target_link_libraries(${ModuleName} PUBLIC
        Qt5::Core
        Qt5::Network
        UTrackerServer::Crypto
)

add_library(UTrackerServer::${ModuleName} ALIAS ${ModuleName})


