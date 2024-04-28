#pragma once

#include <memory>
#include "purple.h"

class Test1App : public purple::IApp{
public:
    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;

private:
    std::shared_ptr<purple::TextureImage> image = nullptr;

    float mTime = 0.0f;

    purple::Shader mCircleSdfShader;
    purple::Shader mSegSdfShader;
    purple::Shader mRectShader;
    purple::Shader mTriangleShader;
    purple::Shader mUnionShader;
    
    void test1();

    void test_circle();
    void test_segment();
    void test_rect();
    void test_triangle();

    void test_boolops();
};