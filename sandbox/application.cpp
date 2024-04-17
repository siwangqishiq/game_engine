#include "application.h"
#include "purple.h"

#include "test1_app.h"

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
    
    glfwSetCharCallback(window , [](GLFWwindow* window_, unsigned int codepoint){
        // std::cout << "ime:" << codepoint << std::endl;
    });

    glfwSetKeyCallback(window , [](GLFWwindow* windows_,int key,int scancode,int action,int mods){
        // purple::Log::w("Application" , "key = %d" , key);
        if(glfwGetKey(windows_, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(windows_, true);
        }
    });

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* windows_,int w,int h){
        // Application* app_ = static_cast<Application *>(glfwGetWindowUserPointer(windows_));
        purple::Engine::resize(w , h);
    });

    if (window == nullptr) {
        purple::Log::e(TAG, "Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    
    purple::Engine::init(screenWidth , screenHeight);

    onCreate();
    if(mAppInstance != nullptr){
        mAppInstance->onInit();
    }
}

void Application::onCreate(){
    mAppInstance = std::make_shared<Test1App>();
}

void Application::tick(){
    purple::Engine::tick();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(mAppInstance != nullptr){
        mAppInstance->onTick();
    }
}

void Application::runLoop(){
    purple::Log::i(TAG , "Application runLoop");
    
    while(!glfwWindowShouldClose(window)) {
        tick();

        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwSwapInterval(1);//锁定固定帧率
    }//end while

    if(mAppInstance != nullptr){
        mAppInstance->onDispose();
    }
    purple::Engine::dispose();
    glfwTerminate();
}

void Application::dispose(){
    purple::Log::i(TAG , "Application dispose");
}

