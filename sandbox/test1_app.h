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

    purple::Shader mSdfShader;

    void test1();
};