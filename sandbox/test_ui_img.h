#pragma once

#include <memory>
#include "purple.h"
#include "ui/ui.h"

class TestImgUi : public purple::IApp{
public:
    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;

    virtual void onResize(int w , int h) override;

private:
    std::shared_ptr<purple::UiRoot> ui = nullptr;
    
    std::shared_ptr<purple::AudioEntity> bgm = nullptr;
    std::shared_ptr<purple::AudioEntity> bgm2 = nullptr;

    void testImg();
    void testImgMatchParent();
    void testImgWrapContent();
    
    void testImgScaleMode();
    void testImgScaleMode2();
    void testImgScaleMode3();
    void testImgScaleMode4();
};