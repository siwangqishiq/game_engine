cmake_minimum_required(VERSION 3.10)

project(app CXX)

set(app "app")
message("statrt to build ${app} ...")

# for dll import use case 
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl -lX11 -latomic")
    set (CMAKE_CXX_FLAGS -pthread)
endif()

if(APPLE)
    message(STATUS "This macos ")
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
    link_directories(lib/mac)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    # 检查是否是树莓派桌面系统
    execute_process(COMMAND uname -a OUTPUT_VARIABLE UNAME_RESULT)
    string(FIND "${UNAME_RESULT}" "raspberrypi" RPI_FOUND)
    if(RPI_FOUND GREATER -1)
        message(STATUS "This is a Raspberry Pi system")
        link_directories(lib/raspi)
    else()
        message(STATUS "This is a Linux system, but not a Raspberry Pi")
    endif()
elseif (UNIX)
    message(STATUS "Using Linux library")
    link_directories(lib/linux)
elseif (UNIX AND NOT APPLE)
    message(STATUS "Using RasPI library")
    link_directories(lib/raspi)
else()
    message(STATUS "This is not a Linux system with ARM architecture")
endif()

link_libraries(glfw3)

add_executable(${PROJECT_NAME} ${SRCS})

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-Wall")
# set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows")

target_link_libraries(${PROJECT_NAME} purple)
target_link_libraries(${PROJECT_NAME} glfw3)








