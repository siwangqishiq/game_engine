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

    std::shared_ptr<purple::AudioEntity> bgm = nullptr;

    void testImg();
    void testImgMatchParent();
    void testImgWrapContent();

    void testImgScaleMode();

    void testImgScaleMode2();

    void testImgScaleMode3();
};