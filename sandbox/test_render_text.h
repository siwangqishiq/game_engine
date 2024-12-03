#pragma once

#include <memory>
#include "purple.h"

class TestTextRender : public purple::IApp{
public:
    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;

private:
    float mTime = 0.0f;
    
    void testTextRender();

    void testTextRenderWithRect();

    void testTextRenderLargeContent();

    void testTextRender2();

    std::wstring novelContent_;

    unsigned int readCount_ = 0;
    unsigned int readOffset_ = 0;

    int renderCharCount_ = -1;
};
