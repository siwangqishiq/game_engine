#include "application.h"
#include "purple.h"

#include "test1_app.h"
#include "test_render_text.h"

int Application::fps = 0;

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
    for(auto &app : appInstanceList){
        app->onInit();
    }//end for each
}

void Application::onCreate(){
    purple::Engine::getTimer()->scheduleAtFixedRate([this](void *app){
        fpsStr = std::to_wstring(fps);
        purple::Log::w("fps" , "fps : %d" , fps);
        fps = 0;
    } , 1000L);
    
    appInstanceList.push_back(std::make_shared<Test1App>());
    appInstanceList.push_back(std::make_shared<TestTextRender>());
}

void Application::tick(){
    purple::Engine::tick();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto &app : appInstanceList){
        app->onTick();
    }//end for each
    
    fps++;
    showDebugInfo();
}

void Application::showDebugInfo(){
    purple::TextPaint paint;
    paint.setTextSize(purple::Engine::ScreenHeight / 15.0f);
    paint.textColor = glm::vec4(0.0f ,1.0f , 0.0f , 1.0f);
    // std::wstring fpsStr = std::to_wstring(fps);
    purple::Rect outputRect;
    outputRect.left = 0.0f;
    outputRect.top = purple::Engine::ScreenHeight;
    outputRect.width = purple::Engine::ScreenWidth;
    outputRect.height = purple::Engine::ScreenHeight;
    paint.textGravity = purple::TopRight;

    purple::Engine::getRenderEngine()->renderTextWithRectV2(fpsStr , outputRect , paint, nullptr);
    // purple::Engine::getRenderEngine()->renderTextWithRect(fpsStr , outputRect , paint, nullptr);
}

void Application::runLoop(){
    purple::Log::i(TAG , "Application runLoop");
    
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        tick();
        glfwSwapBuffers(window);
        glfwSwapInterval(1);//锁定固定帧率
    }//end while

    for(auto &app : appInstanceList){
        app->onDispose();
    }//end for each

    purple::Engine::dispose();
    glfwTerminate();
}

void Application::dispose(){
    purple::Log::i(TAG , "Application dispose");
}

