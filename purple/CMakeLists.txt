cmake_minimum_required(VERSION 3.10)

project(purple)

include_directories(include)

aux_source_directory(src SRCS)

# 动态库
add_library(${PROJECT_NAME} 
                SHARED 
                ${SRCS})

# 静态库
# add_library(${PROJECT_NAME} 
#                 STATIC 
#                 ${SRCS})

target_link_libraries(${PROJECT_NAME} glfw)


