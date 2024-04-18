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
};
