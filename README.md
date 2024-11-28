# 游戏引擎开发笔记

### 什么是游戏引擎?
file -> object for render or play

### 支持平台
- Windwos 
- Linux
- MacOS

### 构建工具 
- cmake

### TODO
1. 工程目录
2. log系统

### 目录说明
    purple 
        引擎主体库
        log 日志 提供三种日志等级 info warn error

        render2d 2D渲染库
            
    sandbox 
        调用purple的应用程序

    vender
        第三方库
        glfw 桌面窗口创建
        

### 构建命令

    mkdir build  
    cd build
    cmake build .. -G"Unix Makefiles"
    cmake --build .
    ./app


### 使用第三方库
桌面窗口 [GLFW](https://www.glfw.org/) 

音频播放 [miniaudio](https://miniaud.io/) 



