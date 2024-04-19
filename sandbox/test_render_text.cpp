#include "test_render_text.h"
#include "render/text_render.h"

void TestTextRender::onInit(){

}

void TestTextRender::onTick(){
    testTextRender();
}

void TestTextRender::onDispose(){

}

void TestTextRender::testTextRender(){
    float left = purple::Engine::ScreenWidth / 2.0f;
    float top = purple::Engine::ScreenHeight / 2.0f;

    purple::TextPaint textPaint;
    textPaint.textColor = glm::vec4(0.0f , 0.0f , 0.0f ,1.0f);
    textPaint.setTextSize(128.0f);
    // purple::Engine::getRenderEngine()->renderText(L"你好 世界!" , 
    //     left , top , textPaint);
    auto textRender = purple::Engine::getRenderEngine()->getTextRender();
    textRender->renderText(L"你好-世界!" , left , top , textPaint);
}

