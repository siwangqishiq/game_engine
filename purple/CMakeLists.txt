cmake_minimum_required(VERSION 3.10)

project(purple)

include_directories(include 
                    vendor)

aux_source_directory(src SRCS)
# aux_source_directory(src/core SRCS_CORE)
# aux_source_directory(src/log SRCS_LOG)

# 动态库
add_library(${PROJECT_NAME} 
                SHARED 
                ${SRCS})

# 静态库
# add_library(${PROJECT_NAME} 
#                 STATIC 
#                 ${SRCS})


