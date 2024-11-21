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

    // auto imgTexture = purple::ImageSource::fromAsset("img/small.png");
    // auto imgTexture = purple::ImageSource::fromAsset("img/la.jpg");
    // auto image = std::make_shared<Img>(imgTexture , 100,500);
    // image->setLayoutGravity<Img>(LayoutGravity::Center)
    //     .setBackgroundColor<Img>(ConverColorValue(Color::Pink))
    //     .setScaleMode<Img>(ImgScale::Mode::FitCenter);
    // container->addChild(image);

    // auto imgTexture = purple::ImageSource::fromAsset("img/la.jpg");
    // auto image = std::make_shared<Img>(imgTexture , 500,500);
    // image->setLayoutGravity<Img>(LayoutGravity::Center)
    //     .setBackgroundColor<Img>(ConverColorValue(Color::Pink))
    //     .setScaleMode<Img>(ImgScale::Mode::FitTop);
    // container->addChild(image);

    auto imgTexture = purple::ImageSource::fromAsset("img/t2.jpg");
    auto image = std::make_shared<Img>(imgTexture , 200,500);
    image->setLayoutGravity<Img>(LayoutGravity::Center)
        .setBackgroundColor<Img>(ConverColorValue(Color::Pink))
        .setScaleMode<Img>(ImgScale::Mode::FitBottom);
    container->addChild(image);

    // auto imgTexture = purple::ImageSource::fromAsset("img/t2.jpg");
    // auto image = std::make_shared<Img>(imgTexture , 200,500);
    // image->setLayoutGravity<Img>(LayoutGravity::Center)
    //     .setBackgroundColor<Img>(ConverColorValue(Color::Pink))
    //     .setScaleMode<Img>(ImgScale::Mode::FitXY);
    // container->addChild(image);

    auto imgTexture2 = purple::ImageSource::fromAsset("img/t2.jpg");
    auto image2 = std::make_shared<Img>(imgTexture2 , 200,200);
    image2->setLayoutGravity<Img>(LayoutGravity::BottomRight);
    container->addChild(image2);

    auto imgTexture3 = purple::ImageSource::fromAsset("img/g2.jpg");
    auto image3 = std::make_shared<Img>(imgTexture3 , 200,200);
    image3->setLayoutGravity<Img>(LayoutGravity::TopRight);
    container->addChild(image3);

    ui->setRootContainer(container);
}

void TestImgUi::onTick(){
    if(ui != nullptr){
        ui->startRenderUI();
    }
}

void TestImgUi::onDispose(){

}

