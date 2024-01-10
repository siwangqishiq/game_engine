#pragma once
#include <string>
#include "GLFW/glfw3.h"

namespace purple{
    class Application{
    public:
        const std::string TAG = "Application";
        //init application
        void init();

        // main loop
        void runLoop();
        
        //on app close
        void dispose();

        int execute(){
            init();
            runLoop();
            dispose();
            return 0;
        }

        GLFWwindow* window = nullptr;
    };
}

