# CORE module

set(ModuleName Crypto)

set(SourceFiles
        Private/CryptoSSL.cpp
)

set(HeaderFiles
        Public/CryptoSSL.h
)


add_library(${ModuleName} STATIC
        ${SourceFiles}
        ${HeaderFiles}
        )

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
        )

add_library(UTrackerServer::${ModuleName} ALIAS ${ModuleName})


