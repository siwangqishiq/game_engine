cmake_minimum_required(VERSION 3.10)

project(pan)

aux_source_directory(. SRCS)

# 动态库
add_library(${PROJECT_NAME} 
                SHARED 
                ${SRCS})