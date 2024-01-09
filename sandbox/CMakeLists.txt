cmake_minimum_required(VERSION 3.10)

project(app)

# for dll import use case 
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(../purple/include)

add_subdirectory(../purple  PURPLE)

aux_source_directory(. SRCS)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} purple)







