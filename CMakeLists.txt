cmake_minimum_required(VERSION 3.25)
project(FileExplorerCBackgroundService)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        libs/sockcpp/include
        libs/RapidFuzz/include
        libs/efsw/include
)
add_subdirectory(libs/sockcpp)
add_subdirectory(libs/RapidFuzz)
add_subdirectory(libs/efsw)


add_subdirectory(src)

add_executable(FileExplorerCBackgroundService src/main.cpp src/connection/SocketConnection.cpp src/connection/SocketConnection.h src/search/FindFiles.cpp src/filesystem/CacheService.cpp src/filesystem/FileSystem.cpp src/filesystem/whereami.c src/filesystem/Events/FileSystemEvents.cpp src/search/search/Search.cpp)

target_link_libraries(FileExplorerCBackgroundService sockpp)
target_link_libraries(FileExplorerCBackgroundService rapidfuzz::rapidfuzz)
target_link_libraries(FileExplorerCBackgroundService efsw)

# Create a custom target to copy sockpp.dll to the build directory
add_custom_target(copy_sockpp_dll ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sockpp>
        $<TARGET_FILE_DIR:FileExplorerCBackgroundService>
        )
add_custom_target(copy_efsw_dll ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:efsw>
        $<TARGET_FILE_DIR:FileExplorerCBackgroundService>
        )


# Add a dependency so that the custom target is executed before building FileExplorerCBackgroundService
add_dependencies(FileExplorerCBackgroundService copy_sockpp_dll copy_efsw_dll)