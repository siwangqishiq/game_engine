#include "test1_app.h"

#include "purple.h"

void Test1App::onInit(){
    purple::Engine::getTimer()->scheduleAtFixedRate([this](void *app){
        purple::Log::w("timer" , "ticker : %lld" , purple::currentTimeMillis());
    } , 1000L);

    image = purple::BuildImageByAsset(std::string("t2.jpg"));

    mCircleSdfShader = purple::ShaderManager::getInstance()
        ->loadAssetShader("sdf" , "shader/shader_vert.glsl","circle_sdf_frag.glsl");
}

void Test1App::test1(){
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
    std::wstring name = L"你好世界 HelloWorld";
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

void Test1App::onTick(){
    purple::Rect rect(0.0f , purple::Engine::ScreenHeight 
        , purple::Engine::ScreenWidth , purple::Engine::ScreenHeight);

    purple::Engine::getRenderEngine()->renderShader(mCircleSdfShader , rect, 
        [this](){
            mCircleSdfShader.setUniformVec2("uSize" 
                , purple::Engine::ScreenWidth 
                , purple::Engine::ScreenHeight);
            
            mCircleSdfShader.setUniformVec4("uColor" 
                ,glm::vec4(0.0f , 0.0f , 1.0f , 1.0f));
        }
    );
}

void Test1App::onDispose(){

}

