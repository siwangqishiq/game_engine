#pragma once
#include <string>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <memory>
#include "purple.h"

class Application{
public:
    const std::string TAG = "SandBoxApp";

    #ifdef __ARM_ARCH //for 树梅派
    const static int screenWidth = 800;
    const static int screenHeight = 600;
    #else
    const static int screenWidth = 1280;
    const static int screenHeight = 720;
    #endif
   

    //init application
    void init();

    void onCreate();
    
    // main loop
    void runLoop();
    
    //on app close
    void dispose();

    //show debug info
    void showDebugInfo();

    void onResize(int w , int h);

    //扩展信息显示
    void showExtensionInfo();
    
    //run this app
    int execute(){
        init();
        runLoop();
        dispose();
        return 0;
    }

    void tick();

    static int fps;
private:
    GLFWwindow* window = nullptr;
    
    std::vector<std::shared_ptr<purple::IApp>> appInstanceList;

    std::wstring fpsStr = L"0";
};

