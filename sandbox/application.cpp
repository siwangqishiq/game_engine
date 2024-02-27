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

    glfwMakeContextCurrent(window);
    
    purple::Engine::init(screenWidth , screenHeight);

    purple::Engine::getTimer()->scheduleAtFixedRate([this](void *app){
        purple::Log::w("timer" , "ticker : %lld" , purple::currentTimeMillis());
    } , 1000L);

    image = purple::BuildImageByAsset(std::string("t2.jpg"));
}

void Application::tick(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    purple::Rect imgDstRect;
    imgDstRect.left = 0.0f;
    imgDstRect.top = purple::Engine::ScreenHeight;
    imgDstRect.width = purple::Engine::ScreenWidth;
    imgDstRect.height = purple::Engine::ScreenHeight;
    auto spriteBatch  = purple::Engine::getRenderEngine()->getSpriteBatch();
    spriteBatch->begin();
    auto src = image->getRect();
    spriteBatch->renderImage(*image , src , imgDstRect);
    spriteBatch->end();

    purple::TextPaint p4;
    p4.setTextSize(purple::Engine::ScreenHeight / 20.0f);
    p4.textColor = glm::vec4(0.0f ,1.0f , 0.0f , 1.0f);
    std::wstring name = L"你好世界";
    std::wstring fpsStr = name;

    purple::Rect outputRect;
    outputRect.left = 0.0f;
    outputRect.top = purple::Engine::ScreenHeight - 16.0f;
    outputRect.width = purple::Engine::ScreenWidth - 16.0f;
    outputRect.height = purple::Engine::ScreenHeight;
    p4.textGravity = purple::TopRight;

    purple::Engine::getRenderEngine()->renderTextWithRect(fpsStr , outputRect , p4 , nullptr);

    purple::Rect rect;
    rect.left = 0.0f;
    rect.top = purple::Engine::ScreenHeight;
    rect.width = purple::Engine::ScreenWidth / 2.0f;
    rect.height = purple::Engine::ScreenHeight / 2.0f;

    purple::Paint rectPaint;
    rectPaint.color = glm::vec4(1.0f , 1.0f , 0.0f , 0.2f); 

    auto batch = purple::Engine::getRenderEngine()->getShapeBatch();
    batch->begin();
    batch->renderRect(rect , rectPaint);
    batch->end();

   
}

void Application::runLoop(){
    purple::Log::i(TAG , "Application runLoop");
    
    while(!glfwWindowShouldClose(window)) {
        purple::Engine::tick();

        tick();

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

