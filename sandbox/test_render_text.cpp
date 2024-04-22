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
    float fontHeight = 200.0f;
    textPaint.setTextSize(fontHeight);

    std::wstring str = L"你好世界 HelloWorld!";

    auto textRender = purple::Engine::getRenderEngine()->getTextRender();
    textRender->renderText(str , left , top , textPaint);

    purple::Engine::getRenderEngine()->renderText(str , 
        left , top + 300.0f , textPaint);
    
    // auto batch = purple::Engine::getRenderEngine()->getShapeBatch();
    // batch->begin();
    // purple::Paint rectPaint;
    // rectPaint.color = glm::vec4(1.0f , 1.0f , 0.0f , 0.4f);
    // purple::Rect rect(left , top + fontHeight , 400.0f , fontHeight);
    // batch->renderRect(rect , rectPaint);
    // batch->end();
}

