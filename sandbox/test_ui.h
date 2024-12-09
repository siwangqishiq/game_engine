#pragma once

#include <memory>
#include "purple.h"
#include "ui/ui.h"

class TestUi : public purple::IApp{
public:
    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;

    virtual void onResize(int w, int h) override{
        onInit();
    }
private:
    float mTime = 0.0f;
    
    std::shared_ptr<purple::UiRoot> ui = nullptr;
    
    void testContainer();
    void testColoumContainer();
    void testColumContainerGravity();
    void testColumContainerWeight();
    void testColumContainerComplex();
    void testRowContainer();
    void testRowContainerGravity();
    void testRowContainerWeight();
    void testRowContainerCompose();
    void testStackContainer();
    void testContainerCompose();


    void testRootUI();
    void testStackContainerWithImage();

    void testColumContainer();

    void testContainerCompose2();

    void testContainerCompose3();
};
