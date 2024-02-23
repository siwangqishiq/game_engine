#include "application.h"
#include "purple.h"

void Application::init(){
    purple::Log::i(TAG , "Application init");
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // glfwWindowHint(GLFW_DECORATED , GLFW_FALSE); 
    // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER , GLFW_TRUE);

    window = glfwCreateWindow(screenWidth, screenHeight, "run", nullptr, nullptr);
    
    if (window == nullptr) {
        purple::Log::e(TAG, "Failed to create GLFW window");
        glfwTerminate();
        return;
    }
    
    purple::Engine::init(screenWidth , screenHeight);
}

void Application::runLoop(){
    purple::Log::i(TAG , "Application runLoop");
    
    while(!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwSwapInterval(1);//锁定固定帧率
    }//end while

    purple::Engine::dispose();
    glfwTerminate();
}

void Application::dispose(){
    purple::Log::i(TAG , "Application dispose");
}

