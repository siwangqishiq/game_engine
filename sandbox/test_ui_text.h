#pragma once

#include <memory>
#include "purple.h"
#include "ui/ui.h"

class TestTextUi : public purple::IApp{
public:
    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;

    virtual void onResize(int w , int h) override;

private:
    std::shared_ptr<purple::UiRoot> ui = nullptr;
    
    void testText();
    void testStackContainerWithText();
};