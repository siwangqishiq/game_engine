#pragma once

#include <memory>
#include "purple.h"
#include "ui/ui.h"

class TestImgUi : public purple::IApp{
public:
    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;

private:
    std::shared_ptr<purple::UiRoot> ui = nullptr;

    void testImg();
    void testImgMatchParent();
    void testImgWrapContent();
};