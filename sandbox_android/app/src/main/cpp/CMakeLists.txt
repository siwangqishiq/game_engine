# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.
project("purple")

set(PURPLE_DIR "../../../../../purple")  #purple源码
set(SANDBOX_DIR "../../../../../sandbox")


include_directories(${PURPLE_DIR}/include) #添加include目录
include_directories(${SANDBOX_DIR})

file(GLOB_RECURSE PURPLE_SRC_FILES ${PURPLE_DIR}/*.cpp)

# 排除特定文件
list(REMOVE_ITEM ALL_SOURCES ${PURPLE_DIR}/glad.cpp)

add_library( # Sets the name of the library.
        purple
        SHARED
        bridge.cpp
        AndroidApplication.cpp
        ${SANDBOX_DIR}/test1_app.cpp
        ${SANDBOX_DIR}/test_render_text.cpp
        ${SANDBOX_DIR}/test_ui.cpp
        ${PURPLE_SRC_FILES}
        )

set(opengl_lib GLESv3)

find_library(log_lib log)

target_link_libraries( # Specifies the target library.
        purple
        ${log_lib}
        ${opengl_lib}
        android
        jnigraphics
        )