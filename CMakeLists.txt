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
include_directories(vender/glfw)

add_subdirectory(purple)
add_subdirectory(vender/glfw)

aux_source_directory(sandbox SRCS)

add_executable(${PROJECT_NAME} ${SRCS})

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-Wall")
# set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows")

target_link_libraries(${PROJECT_NAME} purple)
target_link_libraries(${PROJECT_NAME} glfw)








