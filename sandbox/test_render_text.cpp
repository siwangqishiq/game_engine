#include "test_render_text.h"
#include "render/text_render.h"
#include "resource/asset_manager.h"

void TestTextRender::onInit(){
    novelContent_ = purple::AssetManager::getInstance()->readTextFile("santi3.txt");

    purple::Engine::getTimer()->scheduleAtFixedRate([this](void *){
        readCount_++;
        if(readCount_ >= 200){
            readOffset_ += readCount_;
            readCount_ = 0;
        }
    } ,  100);
}

void TestTextRender::onTick(){
    // testTextRender();
    // testTextRenderWithRect();
    testTextRenderLargeContent();
}

void TestTextRender::onDispose(){

}

void TestTextRender::testTextRenderWithRect(){
    std::wstring str = L"Hello jeep!";

    purple::TextPaint textPaint;
    textPaint.textColor = glm::vec4(0.0f , 1.0f , 1.0f , 1.0f);
    float fontHeight = purple::Engine::ScreenHeight / 5.0f;
    textPaint.setTextSize(fontHeight);
    textPaint.textGravity = purple::TextGravity::TopLeft;
    auto textRender = purple::Engine::getRenderEngine()->getTextRender();

    purple::Rect showRect(0.0f , purple::Engine::ScreenHeight 
        , purple::Engine::ScreenWidth / 2.0f , purple::Engine::ScreenHeight / 2.0f);

    // textRender->renderTextWithRect(str , showRect , textPaint , nullptr);
    textPaint.textGravity = purple::TextGravity::BottomLeft;

    purple::Rect wrapRect;
    textRender->renderTextWithRect(str , showRect , textPaint , &wrapRect);

    auto batch = purple::Engine::getRenderEngine()->getShapeBatch();
    batch->begin();
    purple::Paint rectPaint;
    rectPaint.color = glm::vec4(1.0f , 0.0f , 0.0f , 0.4f);
    batch->renderRect(showRect , rectPaint);
    batch->end();
}

void TestTextRender::testTextRenderLargeContent(){
    purple::TextPaint textPaint;
    textPaint.textColor = glm::vec4(0.0f , 0.0f , 0.0f , 1.0f);
    textPaint.setTextSize(purple::Engine::ScreenHeight / 10.0f);
    textPaint.textGravity = purple::TextGravity::TopLeft;
    auto textRender = purple::Engine::getRenderEngine()->getTextRender();

    purple::Rect showRect(0.0f , purple::Engine::ScreenHeight 
        , purple::Engine::ScreenWidth , purple::Engine::ScreenHeight);
    std::wstring str(novelContent_.begin() + readOffset_ , novelContent_.begin() + readOffset_ + readCount_);
    textRender->renderTextWithRect(str , showRect , textPaint , nullptr);
}

void TestTextRender::testTextRender(){
    float left = purple::Engine::ScreenWidth / 4.0f;
    float top = purple::Engine::ScreenHeight / 2.0f;

    purple::TextPaint textPaint;
    textPaint.textColor = glm::vec4(0.0f , 1.0f , 0.0f ,0.4f);
    float fontHeight = 100.0f;
    textPaint.setTextSize(fontHeight);

    std::wstring str = L"一二三四五六七八九十";

    auto textRender = purple::Engine::getRenderEngine()->getTextRender();
    textRender->renderText(str , 100.0f , top , textPaint);

    // textPaint.setTextSize(170.0f);
    purple::Engine::getRenderEngine()->renderText(str , 
        100.0f , top + 300.0f , textPaint);
    
    auto batch = purple::Engine::getRenderEngine()->getShapeBatch();
    batch->begin();
    purple::Paint rectPaint;
    rectPaint.color = glm::vec4(1.0f , 1.0f , 0.0f , 0.4f);
    purple::Rect rect(left , top + fontHeight , 400.0f , fontHeight);
    batch->renderRect(rect , rectPaint);
    batch->end();
}

