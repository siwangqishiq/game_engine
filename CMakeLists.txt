cmake_minimum_required(VERSION 3.10)

project(app)

# for dll import use case 
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
    set (CMAKE_CXX_FLAGS -pthread)
endif()

include_directories(purple/include)
include_directories(vender/glfw/include)

add_subdirectory(purple)
# add_subdirectory(vender/glfw)

aux_source_directory(sandbox SRCS)

if (WIN32)
    message(STATUS "Using Win32 library")
    link_directories(lib/win64)
elseif (APPLE)
    message(STATUS "Using APPLE library")
elseif (UNIX)
    message(STATUS "Using UNIX library")
endif()

link_libraries(glfw3)

add_executable(${PROJECT_NAME} ${SRCS})

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-Wall")
# set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows")

target_link_libraries(${PROJECT_NAME} purple)
target_link_libraries(${PROJECT_NAME} glfw3)








