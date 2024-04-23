#pragma once

#include "common.h"
#include <memory>
#include "purple.h"

class TestTextRender : public IApp{
public:
    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;

private:
    float mTime = 0.0f;
    
    void testTextRender();

    void testTextRenderWithRect();

    void testTextRenderLargeContent();

    std::wstring novelContent_;

    unsigned int readCount_ = 0;
    unsigned int readOffset_ = 0;

    int renderCharCount_ = -1;
};
