//
// Created by panyi on 2024/4/28.
//

#include "AndroidApplication.h"
#include "test1_app.h"
#include "test_render_text.h"
#include "test_ui.h"

#include <vector>

void AndroidApplication::init(){
    purple::Engine::init(width , height);

    // appInstanceList.push_back(std::make_shared<Test1App>());
    // appInstanceList.push_back(std::make_shared<TestTextRender>());
    appInstanceList.push_back(std::make_shared<UiTest>());
    
    for(std::shared_ptr<purple::IApp> &app : appInstanceList){
        app->onInit();
    }

    purple::Engine::getTimer()->scheduleAtFixedRate([this](void *app){
        purple::Log::w("fps" , "fps : %d" , fps);
        fps = 0;
    } , 1000L);
}

void AndroidApplication::tick(){
    purple::Engine::tick();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(std::shared_ptr<purple::IApp> &app : appInstanceList){
        app->onTick();
    }

    fps++;
}

void AndroidApplication::dispose(){
    for(std::shared_ptr<purple::IApp> &app : appInstanceList){
        app->onDispose();
    }
    purple::Engine::dispose();
}

void AndroidApplication::resize(int w , int h) {
    this->width = w;
    this->height = h;
    purple::Engine::init(w , h);
}

void AndroidApplication::onTouchEvent(int action , float x , float y){
    for(std::shared_ptr<purple::IApp> &app : appInstanceList){
        app->onEvent(action , x , y);
    }
}