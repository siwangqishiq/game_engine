#include "application.h"
#include "purple.h"
#include "input/input_manager.h"

#include "test1_app.h"
#include "test_render_text.h"
#include "test_ui.h"
#include "test_ui_img.h"
#include "test_ui_text.h"

#ifndef __ANDROID__
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#endif

int Application::fps = 0;
bool isFullScreen = false;

bool isMouseLeftPressed = false;
bool isMouseMiddlePressed = false;
bool isMouseRightPressed = false;

void Application::init(){
    purple::Log::i(TAG , "Application init");
    glfwInit();

    #ifdef __ARM_ARCH //for 树梅派
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    #else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #endif
    

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // glfwWindowHint(GLFW_DECORATED , GLFW_FALSE); 
    // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER , GLFW_TRUE);

    GLFWmonitor *mointor = isFullScreen?glfwGetPrimaryMonitor():nullptr;

    window = glfwCreateWindow(screenWidth, screenHeight, "run", mointor, nullptr);
    
    glfwSetCharCallback(window , [](GLFWwindow* window_, unsigned int codepoint){
        // std::cout << "ime:" << codepoint << std::endl;
    });

    glfwSetKeyCallback(window , [](GLFWwindow* windows_,int key,int scancode,int action,int mods){
        // purple::Log::w("Application" , "key = %d" , key);
        if(glfwGetKey(windows_, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(windows_, true);
        }

    });

    glfwSetCursorPosCallback(window , [](GLFWwindow* window, double xpos, double ypos){
        if(isMouseLeftPressed){
            purple::InputEvent event;
            event.action = purple::EVENT_ACTION_MOVE;
            event.x = xpos;
            event.y = Application::screenHeight - ypos;

            purple::InputManager::getInstance()->onEvent(event);
        }
        
        if(isMouseMiddlePressed){
            purple::InputEvent event;
            event.action = purple::EVENT_ACTION_MOUSE_MIDDLE_MOVE;
            event.x = xpos;
            event.y = Application::screenHeight - ypos;

            purple::InputManager::getInstance()->onEvent(event);
        }
        
        if(isMouseRightPressed){
            purple::InputEvent event;
            event.action = purple::EVENT_ACTION_MOUSE_RIGHT_MOVE;
            event.x = xpos;
            event.y = Application::screenHeight - ypos;
            
            purple::InputManager::getInstance()->onEvent(event);
        }
    });

    glfwSetMouseButtonCallback(window , [](GLFWwindow* window, int button, int action, int mods){
        // std::cout << "button : " << button << "  action: " << action 
        //     << " mods : " << mods << std::endl;
        purple::InputEvent event;
        
        // Application* app_ = static_cast<Application *>(glfwGetWindowUserPointer(window));
        if(button == GLFW_MOUSE_BUTTON_LEFT){
            if(action == GLFW_PRESS){
                isMouseLeftPressed = true;
                event.action = purple::EVENT_ACTION_BEGIN; 
            }else if(action == GLFW_RELEASE){
                isMouseLeftPressed = false;
                event.action = purple::EVENT_ACTION_END;
            }
        }else if(button == GLFW_MOUSE_BUTTON_MIDDLE){
            if(action == GLFW_PRESS){
                isMouseMiddlePressed = true;
                event.action = purple::EVENT_ACTION_MOUSE_MIDDLE_BEGIN; 
            }else if(action == GLFW_RELEASE){
                isMouseMiddlePressed = false;
                event.action = purple::EVENT_ACTION_MOUSE_MIDDLE_END; 
            }
        }else if(button == GLFW_MOUSE_BUTTON_RIGHT){
             if(action == GLFW_PRESS){
                isMouseRightPressed = true;
                event.action = purple::EVENT_ACTION_MOUSE_RIGHT_BEGIN; 
            }else if(action == GLFW_RELEASE){
                isMouseRightPressed = false;
                event.action = purple::EVENT_ACTION_MOUSE_RIGHT_END; 
            }
        }
        double x = 0;
        double y = 0;
        glfwGetCursorPos(window, &x, &y);
        event.x = x;
        event.y = Application::screenHeight - y;

        purple::InputManager::getInstance()->onEvent(event);
    });

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* windows_,int w,int h){
        Application* app_ = static_cast<Application *>(glfwGetWindowUserPointer(windows_));
        if(app_ != nullptr){
            app_->onResize(w, h);
        }
    });

    if (window == nullptr) {
        purple::Log::e(TAG, "Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, static_cast<void *>(this));

    #ifndef ANDROID
        #ifdef __ARM_ARCH //for 树梅派
        if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)) {
            return;
        }
        #else
        // glad: load all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            return;
        }
        #endif
    #endif

    purple::Engine::init(screenWidth , screenHeight);
    showExtensionInfo();

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
    
    // appInstanceList.push_back(std::make_shared<Test1App>());
    // appInstanceList.push_back(std::make_shared<TestTextRender>());
    appInstanceList.push_back(std::make_shared<TestUi>());
    // appInstanceList.push_back(std::make_shared<TestImgUi>());
    // appInstanceList.push_back(std::make_shared<TestTextUi>());
}


void Application::tick(){
    // std::cout << " begin tick" << std::endl;
    purple::Engine::tick();

    for(auto &app : appInstanceList){
        app->onTick();
    }//end for each
    
    fps++;
    showDebugInfo();
    // std::cout << " error : " << glGetError() << std::endl;
}

void Application::showExtensionInfo(){
    purple::Log::i(TAG , "===== ExtensionInfo BEGIN====================");
    GLint extensionCount = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS , &extensionCount);
    purple::Log::i(TAG , "ExtensionCount: %d" , extensionCount);
    for(int i = 0 ; i< extensionCount ;i++){
        std::string extensionName = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i));
        // purple::Log::i(TAG , "Extension: \t %s" , extensionName.c_str());
    }//end for i
    purple::Log::i(TAG , "===== ExtensionInfo End =====================");
}

void Application::showDebugInfo(){
    purple::TextPaint paint;
    paint.setTextSize(50.0f);
    paint.textColor = glm::vec4(0.0f ,1.0f , 0.0f , 1.0f);
    // std::wstring fpsStr = std::to_wstring(fps);
    purple::Rect outputRect;
    outputRect.left = 0.0f;
    outputRect.top = purple::Engine::ScreenHeight;
    outputRect.width = purple::Engine::ScreenWidth;
    outputRect.height = purple::Engine::ScreenHeight;
    paint.textGravity = purple::TopRight;
    
    purple::Engine::getRenderEngine()->renderTextWithRectV2(fpsStr , outputRect , paint, nullptr);
}

void Application::onResize(int w, int h){
    purple::Engine::resize(w , h);

    for(auto &app : appInstanceList){
        app->onResize(w, h);
    }//end for each
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

bool Application::onInputEvent(purple::InputEvent &event){
    return false;
}

void Application::dispose(){
    purple::Log::i(TAG , "Application dispose");
}

