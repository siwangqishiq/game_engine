#include "test_ui_img.h"
#include "ui/img.h"
#include "purple_ui.h"

void TestImgUi::onInit(){
    ui = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    // testImg();
    // testImgMatchParent();
    testImgWrapContent();
}

void TestImgUi::testImg(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::SkyBlue));

    auto imgTexture = purple::ImageSource::fromAsset("img/t2.jpg");
    auto image = std::make_shared<Img>(imgTexture , 200,200);
    container->addChild(image);

    ui->setRootContainer(container);
}

void TestImgUi::testImgMatchParent(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::SkyBlue));

    auto imgTexture = purple::ImageSource::fromAsset("img/t2.jpg");
    auto image = std::make_shared<Img>(imgTexture , LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    container->addChild(image);

    ui->setRootContainer(container);
}

void TestImgUi::testImgWrapContent(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::SkyBlue));

    auto imgTexture = purple::ImageSource::fromAsset("img/player_walking.png");
    auto image = std::make_shared<Img>(imgTexture , LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    image->setLayoutGravity<Img>(LayoutGravity::Center);
    container->addChild(image);

    ui->setRootContainer(container);
}

void TestImgUi::onTick(){
    if(ui != nullptr){
        ui->startRenderUI();
    }
}

void TestImgUi::onDispose(){

}

