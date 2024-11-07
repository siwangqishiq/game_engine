#include "test_ui.h"
#include "ui/color.h"


void TestUi::onInit(){
    purple::Log::i("test_ui", "Test Ui init");

    this->ui = std::make_shared<purple::UiRoot>(purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight);

    // this->ui->build([]{ //build widget tree
        
    // });
    using namespace purple;

    PWidget child1 = std::make_shared<Widget>();
    child1->left = 0;
    child1->top = purple::Engine::ScreenHeight;
    child1->width = 200;
    child1->height = 100;
    child1->setBackgroundColor(purple::ConverColorValue(purple::Color::Red));

    PWidget child2 = std::make_shared<Widget>();
    child2->left = 0;
    child2->top = purple::Engine::ScreenHeight - 100;
    child2->width = 200;
    child2->height = 100;
    child2->setBackgroundColor(purple::ConverColorValue(purple::Color::Green));

    PWidget child3 = std::make_shared<Widget>();
    child3->left = 0;
    child3->top = purple::Engine::ScreenHeight - 200;
    child3->width = 200;
    child3->height = 100;
    child3->setBackgroundColor(purple::ConverColorValue(purple::Color::Blue));

    PContainer container = std::make_shared<Container>();
    container->setBackgroundColor(purple::ConverColorValue(purple::Color::White));
    container->addChild(child1);
    container->addChild(child2);
    container->addChild(child3);
    
    this->ui->rootContainer_ = container;
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