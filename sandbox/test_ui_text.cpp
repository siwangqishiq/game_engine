#include "test_ui_text.h"
#include "ui/img.h"
#include "purple_ui.h"
#include "log.h"

void TestTextUi::onInit(){
    ui = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    // testText();
    testStackContainerWithText();
}

void TestTextUi::onResize(int w , int h){
    onInit();
}

void TestTextUi::testText(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::White))
        .setPadding<StackContainer>(0,0,0,0);

    auto text1 = std::make_shared<Text>(L"你好世界" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text1->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(30.0f)
        .setLayoutGravity<Text>(LayoutGravity::TopLeft)
        .setMargin<Text>(0,100,0,0)
        .setBackgroundColor<Text>(ConverColorValue(Color::Red))
        .setPadding<Text>(20,10,20,10);

    container->addChild(text1);

    ui->setRootContainer(container);
}

void TestTextUi::testStackContainerWithText(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::White))
        .setPadding<StackContainer>(0,0,0,0);

    auto text1 = std::make_shared<Text>(L"你好世界" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text1->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(30.0f)
        .setLayoutGravity<Text>(LayoutGravity::TopLeft)
        .setMargin<Text>(0,0,0,0)
        .setBackgroundColor<Text>(ConverColorValue(Color::Pink))
        .setPadding<Text>(20,10,20,10);
    container->addChild(text1);


    auto text2 = std::make_shared<Text>(L"大政奉还" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text2->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(30.0f)
        .setLayoutGravity<Text>(LayoutGravity::TopRight)
        .setBackgroundColor<Text>(ConverColorValue(Color::Yellow))
        .setPadding<Text>(20,10,20,10);
    container->addChild(text2);


    auto text3 = std::make_shared<Text>(L"天诛\n国贼" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text3->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(80.0f)
        .setLayoutGravity<Text>(LayoutGravity::Center)
        .setBackgroundConnerRadius<Text>(16.0f)
        .setBackgroundColor<Text>(ConverColorValue(Color::Red))
        .setPadding<Text>(20,20,20,20);
    container->addChild(text3);

    auto text4 = std::make_shared<Text>(L"废刀令" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text4->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(30.0f)
        .setLayoutGravity<Text>(LayoutGravity::BottomLeft)
        .setBackgroundColor<Text>(ConverColorValue(Color::SkyBlue))
        .setPadding<Text>(20,10,20,10);
    container->addChild(text4);

    auto text5 = std::make_shared<Text>(L"黑船来袭" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text5->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(30.0f)
        .setLayoutGravity<Text>(LayoutGravity::BottomRight)
        .setBackgroundColor<Text>(ConverColorValue(Color::SkyBlue))
        .setPadding<Text>(20,10,20,10);
    container->addChild(text5);

    ui->setRootContainer(container);
}

void TestTextUi::onTick(){
    if(ui != nullptr){
        ui->startRenderUI();
    }
}

void TestTextUi::onDispose(){
    purple::Log::i("TestImgUi","TestTextUi::onDispose");
}

