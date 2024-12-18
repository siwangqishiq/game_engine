#pragma once

#include <memory>
#include "purple.h"
#include "purple_ui.h"

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
    void testColumContainer();
    void testColumContainerInStack();
};