cmake_minimum_required(VERSION 3.25)
project(FileExplorerC)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        libs/raylib/include
        libs/raylib/src/external/glfw/include
)

add_subdirectory(libs/raylib)

add_custom_target(
        copy_resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources

)

add_executable(FileExplorerC src/main.cpp src/render/filesystem/FileSystem.cpp src/render/filesystem/FileSystem.h src/render/App.cpp src/render/components/FileSystemView.cpp src/render/components/FileSystemView.h src/render/filesystem/whereami.c)
target_link_libraries(FileExplorerC raylib)
add_dependencies(FileExplorerC copy_resources)