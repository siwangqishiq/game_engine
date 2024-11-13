#include "test_ui.h"
#include "ui/color.h"
#include "ui/text.h"
#include "ui/colum_container.h"

void TestUi::testContainer(){
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

void TestUi::testColoumContainer(){
    using namespace purple;

    auto container = std::make_shared<Container>();
    
    container->setBackgroundColor<Container>(ConverColorValue(Color::Purple))
        .setBackgroundConnerRadius<Container>(20.0f);

    std::shared_ptr<Text> text1 = std::make_shared<Text>(L"Hello World 你好世界23333~",
        LAYOUT_MATCH_PARENT,
        LAYOUT_WRAP_CONTENT);
    text1->setBackgroundColor<Text>(ConverColorValue(Color::Red))
        .setPosition<Text>(100,purple::Engine::ScreenHeight)
        .setFontColor<Text>(ConverColorValue(Color::Blue))
        .setFontSize<Text>(100.0f);
    container->addChild(text1);

    std::shared_ptr<Text> text2 = std::make_shared<Text>(L"Hello World",
        LAYOUT_WRAP_CONTENT,
        LAYOUT_WRAP_CONTENT);
    text2->setBackgroundColor<Text>(ConverColorValue(Color::Green))
        .setPosition<Text>(100,purple::Engine::ScreenHeight);
    container->addChild(text2);

    std::shared_ptr<Text> text3 = std::make_shared<Text>(L"你好世界\nHello",
        LAYOUT_WRAP_CONTENT,
        LAYOUT_WRAP_CONTENT);
    text3->setBackgroundColor<Text>(ConverColorValue(Color::Blue))
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setPosition<Text>(100,purple::Engine::ScreenHeight);
    container->addChild(text3);

    this->ui->rootContainer_ = container;
}


void TestUi::onInit(){
    purple::Log::i("test_ui", "Test Ui init");

    this->ui = std::make_shared<purple::UiRoot>(purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight);

    // testContainer();
    testColoumContainer();
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