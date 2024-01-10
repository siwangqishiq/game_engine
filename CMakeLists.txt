cmake_minimum_required(VERSION 3.10)

project(app)

# for dll import use case 
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(purple/include)
include_directories(vender/panlib)
include_directories(vender/glfw)

add_subdirectory(purple)
add_subdirectory(vender/panlib)
add_subdirectory(vender/glfw)

aux_source_directory(sandbox SRCS)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} purple)
target_link_libraries(${PROJECT_NAME} pan)
target_link_libraries(${PROJECT_NAME} glfw)








