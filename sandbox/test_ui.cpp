#include "test_ui.h"
#include "ui/color.h"
#include "ui/text.h"


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
    child1->setSize<Widget>(200,100)
        .setBackgroundColor<Widget>(purple::ConverColorValue(purple::Color::Red));

    PWidget child2 = std::make_shared<Widget>();
    child2->left = 0;
    child2->top = purple::Engine::ScreenHeight - 100;
    child2->setSize<Widget>(200,100)
        .setBackgroundColor<Widget>(purple::ConverColorValue(purple::Color::Green));

    PWidget child3 = std::make_shared<Widget>();
    child3->left = 0;
    child3->top = purple::Engine::ScreenHeight - 200;
    child3->setSize<Widget>(200,100)
        .setBackgroundColor<Widget>(purple::ConverColorValue(purple::Color::Blue));


    PContainer container = std::make_shared<Container>();
    container->setBackgroundColor<Widget>(purple::ConverColorValue(purple::Color::White));
    container->addChild(child1);
    container->addChild(child2);
    container->addChild(child3);

    std::shared_ptr<Text> textChild = std::make_shared<Text>(L"Hello World 你好世界!",
        LAYOUT_MATCH_PARENT,
        LAYOUT_WRAP_CONTENT);
    textChild->left = 0;
    textChild->top = purple::Engine::ScreenHeight - 300 - 20;
    
    textChild->setBackgroundColor<Text>(purple::ConverColorValue(purple::Color::Green))
        .setFontSize<Text>(50.0f)
        .setFontColor<Text>(purple::ConverColorValue(purple::Color::Black))
        .setBackgroundConnerRadius<Text>(16.0f)
        .setPadding<Text>(10,10,10,10)
        .setTextGravity<Text>(TextGravity::TopCenter);

    container->addChild(textChild);
    
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