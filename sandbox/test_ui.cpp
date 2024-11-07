#include "test_ui.h"


void TestUi::onInit(){
    purple::Log::i("test_ui", "Test Ui init");

    this->ui = std::make_shared<purple::UiRoot>(purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight);

    // this->ui->build([]{ //build widget tree
        
    // });
}

void TestUi::onTick(){
    // purple::Log::i("test_ui", "Test Ui onTick");

    if(this->ui != nullptr){
        this->ui->startRenderUI();
    }
}

void TestUi::onDispose(){
    purple::Log::i("test_ui", "Test Ui onDispose");
}