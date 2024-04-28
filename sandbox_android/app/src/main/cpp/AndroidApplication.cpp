//
// Created by panyi on 2024/4/28.
//

#include "AndroidApplication.h"
#include "purple.h"

void AndroidApplication::init(){
    purple::Engine::init(width , height);
}

void AndroidApplication::tick(){
    purple::Engine::tick();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void AndroidApplication::dispose(){

}

void AndroidApplication::resize(int w , int h){
    purple::Engine::init(w , h);
}

void AndroidApplication::onTouchEvent(int action , float x , float y){

}