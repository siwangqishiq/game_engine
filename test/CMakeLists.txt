cmake_minimum_required(VERSION 3.10)

project(test_app CXX)

# 启用测试
enable_testing()

set(test_app_name "test_app")
message("start buid ${appname} ...")

add_subdirectory(../purple build)

if (WIN32)
    message(STATUS "Using Win32 library")
    link_directories(../lib/win64)
elseif (APPLE)
    message(STATUS "Using APPLE library")
    link_directories(../lib/mac)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    # 检查是否是树莓派桌面系统
    execute_process(COMMAND uname -a OUTPUT_VARIABLE UNAME_RESULT)
    string(FIND "${UNAME_RESULT}" "raspberrypi" RPI_FOUND)
    if(RPI_FOUND GREATER -1)
        message(STATUS "This is a Raspberry Pi system")
        link_directories(../lib/raspi)
    else()
        message(STATUS "This is a Linux system, but not a Raspberry Pi")
    endif()
elseif (UNIX)
    message(STATUS "Using Linux library")
    link_directories(../lib/linux)
elseif (UNIX AND NOT APPLE)
    message(STATUS "Using RasPI library")
    link_directories(../lib/raspi)
else()
    message(STATUS "This is not a Linux system with ARM architecture")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl -lX11 -latomic")
    set (CMAKE_CXX_FLAGS -pthread)
endif()

include_directories(../purple/include)
include_directories(../vender/glfw/include)

# 引用本地的 GoogleTest
add_subdirectory(googletest)

file(GLOB TEST_SOURCES "*.cpp")

# 添加源文件和测试文件
add_executable(${test_app_name} ${TEST_SOURCES})

# 链接 GoogleTest 库
target_link_libraries(${test_app_name} gtest gtest_main)

# 
target_link_libraries(${test_app_name} purple)


# 添加测试
add_test(NAME test_purple COMMAND ${test_app_name})












