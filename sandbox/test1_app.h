#pragma once

#include "common.h"
#include <memory>
#include "purple.h"

class Test1App : public IApp{
public:
    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;

private:
    std::shared_ptr<purple::TextureImage> image = nullptr;

    purple::Shader mCircleSdfShader;
    purple::Shader mSegSdfShader;
    purple::Shader mRectShader;
    
    void test1();

    void test_circle();
    void test_segment();
    void test_rect();
};