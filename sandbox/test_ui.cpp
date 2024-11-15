#include "test_ui.h"
#include "ui/color.h"
#include "ui/text.h"
#include "ui/colum_container.h"
#include "ui/row_container.h"

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

    auto container = std::make_shared<ColumContainer>();
    
    container->setBackgroundColor<ColumContainer>(ConverColorValue(Color::White))
        .setBackgroundConnerRadius<ColumContainer>(10.0f);

    std::shared_ptr<Text> text1 = std::make_shared<Text>(L"Hello World 你好世界1234567890~你好世界1234567890~",
        LAYOUT_MATCH_PARENT,
        LAYOUT_WRAP_CONTENT);
    text1->setBackgroundColor<Text>(ConverColorValue(Color::Red))
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setBackgroundConnerRadius<Text>(10.0f)
        .setFontSize<Text>(80.0f)
        .setPadding<Text>(10,10,10,10)
        .setMargin<Text>(20,20,20,0);
    container->addChild(text1);

    std::shared_ptr<Text> text2 = std::make_shared<Text>(L"HelloWorld",
        LAYOUT_WRAP_CONTENT,
        LAYOUT_WRAP_CONTENT);
    text2->setBackgroundColor<Text>(ConverColorValue(Color::Purple))
        .setBackgroundConnerRadius<Text>(10.0f)
        .setPadding<Text>(10,10,10,10)
        .setMargin<Text>(10,10,0,0);
    container->addChild(text2);

    std::shared_ptr<Text> text3 = std::make_shared<Text>(L"你好世界\nHello",
        LAYOUT_WRAP_CONTENT,
        LAYOUT_WRAP_CONTENT);
    text3->setBackgroundColor<Text>(ConverColorValue(Color::Blue))
        .setFontColor<Text>(ConverColorValue(Color::Purple))
        .setBackgroundConnerRadius<Text>(10.0f)
        .setMargin<Text>(0,10,0,0)
        .setPadding<Text>(20,20,20,20);
    container->addChild(text3);

    this->ui->rootContainer_ = container;
}

void TestUi::testColumContainerGravity(){
    using namespace purple;

    auto container = std::make_shared<ColumContainer>();
    container->setBackgroundColor<ColumContainer>(ConverColorValue(Color::White))
        .setPadding<ColumContainer>(20,20,20,20)
        .setSize<ColumContainer>(400, LAYOUT_MATCH_PARENT)
        .setBackgroundConnerRadius<ColumContainer>(0.0f);

    auto cube1 = std::make_shared<Widget>(100,100);
    cube1->setBackgroundColor<Widget>(ConverColorValue(Color::Purple))
        .setMargin<Widget>(0,10,20,10)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube1);

    auto cube2 = std::make_shared<Widget>(100,100);
    cube2->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setMargin<Widget>(0,10,0,10)
        .setLayoutGravity<Widget>(LayoutGravity::TopCenter)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube2);

    auto cube3 = std::make_shared<Widget>(100,100);
    cube3->setBackgroundColor<Widget>(ConverColorValue(Color::SkyBlue))
        .setMargin<Widget>(20,10,0,10)
        .setLayoutGravity<Widget>(LayoutGravity::TopRight)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube3);

    auto text1 = std::make_shared<Text>(L"Hello World",LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    text1->setBackgroundColor<Text>(ConverColorValue(Color::Yellow))
        .setFontSize<Text>(64.0f)
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setLayoutGravity<Text>(LayoutGravity::TopCenter);
    container->addChild(text1);
    
    ui->rootContainer_ = container;
}

void TestUi::testColumContainerWeight(){
     using namespace purple;

    auto container = std::make_shared<ColumContainer>();
    container->setBackgroundColor<ColumContainer>(ConverColorValue(Color::White))
        .setSize<ColumContainer>(LAYOUT_MATCH_PARENT, 600)
        .setBackgroundConnerRadius<ColumContainer>(0.0f);

    auto cube1 = std::make_shared<Widget>(100,100);
    cube1->setBackgroundColor<Widget>(ConverColorValue(Color::Purple))
        .setMargin<Widget>(0,0,20,10)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube1);

    auto cube2 = std::make_shared<Widget>(100,100);
    cube2->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setMargin<Widget>(0,10,0,10)
        .setLayoutGravity<Widget>(LayoutGravity::TopCenter)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube2);

    auto cube3 = std::make_shared<Widget>(LAYOUT_MATCH_PARENT,0);
    cube3->setBackgroundColor<Widget>(ConverColorValue(Color::SkyBlue))
        .setMargin<Widget>(0,10,0,10)
        .setLayoutWeight<Widget>(1)
        .setLayoutGravity<Widget>(LayoutGravity::TopRight)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube3);

    auto text1 = std::make_shared<Text>(L"你好呀~",LAYOUT_MATCH_PARENT,LAYOUT_WRAP_CONTENT);
    text1->setBackgroundColor<Text>(ConverColorValue(Color::Yellow))
        .setFontSize<Text>(64.0f)
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setLayoutWeight<Text>(1)
        .setTextGravity<Text>(TextGravity::Center)
        .setLayoutGravity<Text>(LayoutGravity::TopCenter);
    container->addChild(text1);
    
    ui->rootContainer_ = container;
}

void TestUi::testColumContainerComplex(){
    using namespace purple;

    auto container = std::make_shared<ColumContainer>();
    container->setBackgroundColor<ColumContainer>(ConverColorValue(Color::White))
        .setSize<ColumContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT)
        .setBackgroundConnerRadius<ColumContainer>(0.0f);

    auto cube1 = std::make_shared<Widget>(100,100);
    cube1->setBackgroundColor<Widget>(ConverColorValue(Color::Purple))
        .setMargin<Widget>(0,0,20,10)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube1);

    auto childContainer = std::make_shared<ColumContainer>(500,200);
    childContainer->setBackgroundColor<ColumContainer>(ConverColorValue(Color::Blue));
    childContainer->setId<ColumContainer>("outter_view");
    auto text1 = std::make_shared<Text>(L"Hello",
        LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    text1->setFontSize<Text>(64.0f)
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setLayoutWeight<Text>(1)
        .setTextGravity<Text>(TextGravity::Center)
        .setId<Text>("inner_text");
    childContainer->addChild(text1);

    auto text2 = std::make_shared<Text>(L"Hello2",
        LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    text2->setFontSize<Text>(64.0f)
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setLayoutWeight<Text>(1)
        .setTextGravity<Text>(TextGravity::Center)
        .setId<Text>("inner_text");
    childContainer->addChild(text2);

    container->addChild(childContainer);

    auto cube2 = std::make_shared<Widget>(100,100);
    cube2->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setMargin<Widget>(0,10,0,10)
        .setLayoutGravity<Widget>(LayoutGravity::TopCenter)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube2);

    auto cube3 = std::make_shared<Widget>(LAYOUT_MATCH_PARENT,0);
    cube3->setBackgroundColor<Widget>(ConverColorValue(Color::SkyBlue))
        .setMargin<Widget>(0,10,0,10)
        .setLayoutWeight<Widget>(1)
        .setLayoutGravity<Widget>(LayoutGravity::TopRight)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube3);

    
    ui->rootContainer_ = container;
}

void TestUi::testRowContainer(){
    using namespace purple;

    auto container = std::make_shared<RowContainer>();
    container->setBackgroundColor<RowContainer>(ConverColorValue(Color::White))
        .setSize<RowContainer>(LAYOUT_MATCH_PARENT, LAYOUT_WRAP_CONTENT)
        .setBackgroundConnerRadius<RowContainer>(30.0f);

    auto cube1 = std::make_shared<Widget>(100,100);
    cube1->setBackgroundColor<Widget>(ConverColorValue(Color::Purple))
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube1);

    auto cube2 = std::make_shared<Widget>(100,100);
    cube2->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setMargin<Widget>(0,10,0,10)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube2);

    auto text1 = std::make_shared<Text>(L"Hello你好",
        LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    text1->setFontSize<Text>(64.0f)
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setLayoutWeight<Text>(1)
        .setTextGravity<Text>(TextGravity::Center);
    container->addChild(text1);

    auto cube3 = std::make_shared<Widget>(200,300);
    cube3->setBackgroundColor<Widget>(ConverColorValue(Color::SkyBlue))
        .setMargin<Widget>(80,10,0,10)
        .setLayoutWeight<Widget>(1)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube3);

    ui->rootContainer_ = container;
}


void TestUi::onInit(){
    purple::Log::i("test_ui", "Test Ui init");

    this->ui = std::make_shared<purple::UiRoot>(purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight);

    // testContainer();
    // testColoumContainer();
    // testColumContainerGravity();
    // testColumContainerWeight();
    // testColumContainerComplex();
    testRowContainer();
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