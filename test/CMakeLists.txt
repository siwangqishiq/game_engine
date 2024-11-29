cmake_minimum_required(VERSION 3.10)

project(test_app CXX)

# 启用测试
enable_testing()

set(test_app_name "test_app")
message("start buid ${appname} ...")

include_directories(../purple/include)
include_directories(../sandbox)
include_directories(../vender/glfw/include)

# 引用本地的 GoogleTest
add_subdirectory(googletest)

file(GLOB TEST_SOURCES "*.cpp")

# 添加源文件和测试文件
add_executable(${test_app_name} ${TEST_SOURCES})

# 链接 GoogleTest 库
target_link_libraries(${test_app_name} gtest gtest_main)

# 添加测试
add_test(NAME test_purple COMMAND ${test_app_name})










