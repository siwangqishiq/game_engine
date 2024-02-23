#pragma once
#include <string>
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

private:
    GLFWwindow* window = nullptr;
    int screenWidth = 800;
    int screenHeight = 600;
};

