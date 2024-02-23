#pragma once
#include <string>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

class Application{
public:
    const std::string TAG = "SandBoxApp";
    //init application
    void init();
    
    // main loop
    void runLoop();
    
    //on app close
    void dispose();
    
    //run this app
    int execute(){
        init();
        runLoop();
        dispose();
        return 0;
    }

    void tick();

private:
    GLFWwindow* window = nullptr;
    int screenWidth = 800;
    int screenHeight = 600;
};

