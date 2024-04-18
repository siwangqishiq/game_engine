#include "test1_app.h"

#include "purple.h"

void Test1App::onInit(){
    image = purple::BuildImageByAsset(std::string("t2.jpg"));

    mCircleSdfShader = purple::ShaderManager::getInstance()
        ->loadAssetShader("sdf_circle" , "shader/shader_vert.glsl","circle_sdf_frag.glsl");

    mSegSdfShader = purple::ShaderManager::getInstance()
        ->loadAssetShader("sdf_line" , "shader/shader_vert.glsl","segment_sdf_frag.glsl");

    mRectShader = purple::ShaderManager::getInstance()
        ->loadAssetShader("sdf_rect" , "shader/shader_vert.glsl","rect_sdf_frag.glsl");
    
    mUnionShader = purple::ShaderManager::getInstance()
        ->loadAssetShader("union_rect" , "shader/shader_vert.glsl","union_sdf_frag.glsl");

    mTriangleShader = purple::ShaderManager::getInstance()
        ->loadAssetShader("sdf_triangle" , "shader/shader_vert.glsl" ,"triangle_sdf_frag.glsl");
}



void Test1App::onTick(){
    // test_circle();
    // test_segment();
    test_rect();
    // test_triangle();
    // test_boolops();

    mTime += 0.02f;
}

void Test1App::test_boolops(){
    purple::Rect rect(0.0f , purple::Engine::ScreenHeight 
        , purple::Engine::ScreenWidth , purple::Engine::ScreenHeight);
    
    purple::Engine::getRenderEngine()->renderShader(mUnionShader , rect, 
        [this , rect](){
            mUnionShader.setUniformVec2("uSize" 
                , purple::Engine::ScreenWidth 
                , purple::Engine::ScreenHeight);

            mUnionShader.setUniformVec4("uColor" 
                ,glm::vec4(0.0f , 0.0f , 1.0f , 1.0f));
        }
    );
}

void Test1App::test_rect(){
    purple::Rect rect(0.0f , purple::Engine::ScreenHeight 
        , purple::Engine::ScreenWidth , purple::Engine::ScreenHeight);
    
    purple::Engine::getRenderEngine()->renderShader(mRectShader , rect, 
        [this , rect](){
            mRectShader.setUniformVec2("uSize" 
                , purple::Engine::ScreenWidth 
                , purple::Engine::ScreenHeight);

            mRectShader.setUniformVec4("uColor" 
                ,glm::vec4(1.0f , 0.0f , 0.0f , 1.0f));
            float A = rect.height / 8.0f;
            mRectShader.setUniformFloat("uRoundRadius" , 
                A + A * glm::sin(mTime));

            mRectShader.setUniformVec2("uRectSize" , purple::Engine::ScreenWidth / 2.0f , 
                purple::Engine::ScreenHeight / 2.0f);
            mRectShader.setUniformVec2("uRectPos" 
                , rect.width / 2.0f
                , rect.height / 2.0f);
        }
    );
}

void Test1App::test_triangle(){
    purple::Rect rect(0.0f , purple::Engine::ScreenHeight 
        , purple::Engine::ScreenWidth , purple::Engine::ScreenHeight);

    purple::Engine::getRenderEngine()->renderShader(mTriangleShader , rect, 
        [this](){
            mTriangleShader.setUniformVec2("uSize" 
                , purple::Engine::ScreenWidth 
                , purple::Engine::ScreenHeight);

            mTriangleShader.setUniformVec4("uColor" 
                ,glm::vec4(0.5f + 0.5f * glm::sin(mTime) , 0.0f , 0.0f , 1.0f));

            glm::vec2 center(purple::Engine::ScreenWidth / 2.0f , purple::Engine::ScreenHeight / 2.0f );
            float delta = purple::Engine::ScreenHeight / 4.0f;
            glm::vec2 p1 = center + glm::vec2(0.0f , delta);
            glm::vec2 p2 = center + glm::vec2(-delta , -delta);
            glm::vec2 p3 = center + glm::vec2(delta , -delta);

            mTriangleShader.setUniformVec2("uP1" , p1);
            mTriangleShader.setUniformVec2("uP2" , p2);
            mTriangleShader.setUniformVec2("uP3" , p3);
        }
    );
}

void Test1App::test_segment(){
    purple::Rect rect(0.0f , purple::Engine::ScreenHeight 
        , purple::Engine::ScreenWidth , purple::Engine::ScreenHeight);

    purple::Engine::getRenderEngine()->renderShader(mSegSdfShader , rect, 
        [this](){
            mSegSdfShader.setUniformVec2("uSize" 
                , purple::Engine::ScreenWidth 
                , purple::Engine::ScreenHeight);

            mSegSdfShader.setUniformVec4("uColor" 
                ,glm::vec4(1.0f , 0.0f , 0.0f , 1.0f));
            
            mSegSdfShader.setUniformVec2("uP1" , glm::vec2(100.0f , 100.0f));
            mSegSdfShader.setUniformVec2("uP2" , glm::vec2(200.0f , 500.0f));
        }
    );
}


void Test1App::onDispose(){

}

void Test1App::test_circle(){
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

