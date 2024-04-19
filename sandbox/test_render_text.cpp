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
    float left = purple::Engine::ScreenWidth / 4.0f;
    float top = purple::Engine::ScreenHeight / 2.0f;

    purple::TextPaint textPaint;
    textPaint.textColor = glm::vec4(1.0f , 0.0f , 0.0f ,1.0f);
    textPaint.setTextSize(256.0f);

    std::wstring str = L"你好 世界!HelloWorld";
    purple::Engine::getRenderEngine()->renderText(str , 
        left , top + textPaint.getTextFontHeight() , textPaint);
    auto textRender = purple::Engine::getRenderEngine()->getTextRender();
    textRender->renderText(str , left , top , textPaint);
}

