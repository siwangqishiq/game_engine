#include "application.h"
#include "log.h"

namespace purple{
    void Application::init(){
        Log::i(TAG , "Application init");
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(800, 600, "run", nullptr, nullptr);
        
        if (window == nullptr) {
            Log::e(TAG, "Failed to create GLFW window");
            glfwTerminate();
            return;
        }
    }

    void Application::runLoop(){
        Log::i(TAG , "Application runLoop");

        while(!glfwWindowShouldClose(window)) {
            // std::cout << "tick" << std::endl;
            glfwSwapBuffers(window);
            glfwPollEvents();
            glfwSwapInterval(1);//锁定固定帧率
        }//end while

        glfwTerminate();
    }

    void Application::dispose(){
        Log::i(TAG , "Application dispose");
    }

}//end purple namespace

