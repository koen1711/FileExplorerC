
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Running on Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_subdirectory(linux)
    message(STATUS "Running on Linux")
else()
    message(FATAL_ERROR "Unsupported system: ${CMAKE_SYSTEM_NAME}")
endif()

