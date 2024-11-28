#include "test_ui_img.h"
#include "ui/img.h"
#include "purple_ui.h"
#include "log.h"

void TestImgUi::onInit(){
    ui = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    // testImg();
    // testImgMatchParent();
    // testImgWrapContent();
    // testImgScaleMode();
    // testImgScaleMode2();
    // testImgScaleMode3();
    testImgScaleMode4();
    
    // std::string audioPath = "audio/heishenhua.mp3";
    // bgm = purple::AudioManager::getInstance()->loadAudioEntity(audioPath,false);

    // std::string audioPath2 = "audio/test.mp3";
    // bgm2 = purple::AudioManager::getInstance()->loadAudioEntity(audioPath2,false);


    // purple::AudioManager::getInstance()->setAudioPlayEndCallback(bgm, [this](std::string name){
    //     purple::AudioManager::getInstance()->playAudioEntity(this->bgm2);
    // });

    // purple::AudioManager::getInstance()->setAudioPlayEndCallback(bgm2, [this](std::string name){
    //     purple::AudioManager::getInstance()->playAudioEntity(this->bgm);
    // });
    
    // // purple::AudioManager::getInstance()->playAudioEntity(bgm);
    // purple::AudioManager::getInstance()->playAudioEntity(bgm2);
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

    auto imgTexture = purple::ImageSource::fromAsset("img/small.png");
    auto image = std::make_shared<Img>(imgTexture , LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    image->setLayoutGravity<Img>(LayoutGravity::Center)
        .setBackgroundColor<Img>(ConverColorValue(Color::Pink))
        .setScaleMode<Img>(ImgScale::Mode::FitBottom);
    container->addChild(image);

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

void TestImgUi::testImgScaleMode(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::White));

    auto imgTexture = purple::ImageSource::fromAsset("img/g2.jpg");

    auto imageBase = std::make_shared<Img>(imgTexture , LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    imageBase->setLayoutGravity<Img>(LayoutGravity::Center)
        .setScaleMode<Img>(ImgScale::Mode::Center);
    container->addChild(imageBase);

    auto image = std::make_shared<Img>(300,300);
    image->setLayoutGravity<Img>(LayoutGravity::Center)
        .setBackgroundColor<Img>(ConverColorValue(Color::SkyBlue))
        .setScaleMode<Img>(ImgScale::Mode::Center);
    container->addChild(image);
    
    ui->setRootContainer(container);

    purple::Engine::getTimer()->schedule([image, imgTexture](void *){
        image->setImage<Img>(imgTexture);
    },4000);
}

void TestImgUi::testImgScaleMode2(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::White));

    auto imgTexture = purple::ImageSource::fromAsset("img/small.png");

    auto image = std::make_shared<Img>(imgTexture, 400,400);
    image->setLayoutGravity<Img>(LayoutGravity::Center)
        .setBackgroundColor<Img>(ConverColorValue(Color::SkyBlue))
        .setPadding<Img>(10,10,10,10)
        .setScaleMode<Img>(ImgScale::Mode::CenterCrop);
    container->addChild(image);
    
    ui->setRootContainer(container);
}

void TestImgUi::testImgScaleMode3(){
    using namespace purple;

    auto container = std::make_shared<RowContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);

    // auto imgTexture = purple::ImageSource::fromAsset("img/g2.jpg");
    // auto imgTexture = purple::ImageSource::fromAsset("img/small.png");

    auto imgTexture1 = purple::ImageSource::fromAsset("img/more_height.jpg");
    auto imgTexture2 = purple::ImageSource::fromAsset("img/g2.jpg");
    const int imageSizeWidth = 400;
    const int imageSizeHeight = 400;

    auto leftContainer = std::make_shared<StackContainer>(0,LAYOUT_MATCH_PARENT);
    leftContainer->setBackgroundColor<StackContainer>(ConverColorValue(Color::Silver))
        .setLayoutWeight<StackContainer>(1);
    container->addChild(leftContainer);
    auto leftImage = std::make_shared<Img>(imgTexture1 , imageSizeWidth,imageSizeHeight);
    leftImage->setLayoutGravity<Img>(LayoutGravity::Center)
        .setPadding<Img>(5,5,5,5)
        .setScaleMode<Img>(ImgScale::Mode::CenterCrop)
        .setBackgroundColor<Img>(ConverColorValue(Color::Pink));
    leftContainer->addChild(leftImage);

    auto rightContainer = std::make_shared<StackContainer>(0,LAYOUT_MATCH_PARENT);
    rightContainer->setBackgroundColor<StackContainer>(ConverColorValue(Color::SkyBlue))
        .setLayoutWeight<StackContainer>(1);
    container->addChild(rightContainer);
    auto rightImage = std::make_shared<Img>(imgTexture1 , imageSizeWidth,imageSizeHeight);
    rightImage->setLayoutGravity<Img>(LayoutGravity::Center)
        .setPadding<Img>(5,5,5,5)
        .setScaleMode<Img>(ImgScale::Mode::CenterInside)
        .setBackgroundColor<Img>(ConverColorValue(Color::Pink));
    rightContainer->addChild(rightImage);

    ui->setRootContainer(container);
}

void TestImgUi::testImgScaleMode4(){
    using namespace purple;

    auto container = std::make_shared<RowContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);

    // auto imgTexture = purple::ImageSource::fromAsset("img/g2.jpg");
    // auto imgTexture = purple::ImageSource::fromAsset("img/small.png");

    auto imgTexture2 = purple::ImageSource::fromAsset("img/g2.jpg");
    const int imageSizeWidth = 400;
    const int imageSizeHeight = 400;

    auto leftContainer = std::make_shared<StackContainer>(0,LAYOUT_MATCH_PARENT);
    leftContainer->setBackgroundColor<StackContainer>(ConverColorValue(Color::Silver))
        .setLayoutWeight<StackContainer>(1);
    container->addChild(leftContainer);
    auto leftImage = std::make_shared<Img>(imgTexture2 , imageSizeWidth,imageSizeHeight);
    leftImage->setLayoutGravity<Img>(LayoutGravity::Center)
        .setPadding<Img>(5,5,5,5)
        .setScaleMode<Img>(ImgScale::Mode::CenterCrop)
        .setBackgroundColor<Img>(ConverColorValue(Color::Pink));
    leftContainer->addChild(leftImage);

    auto rightContainer = std::make_shared<StackContainer>(0,LAYOUT_MATCH_PARENT);
    rightContainer->setBackgroundColor<StackContainer>(ConverColorValue(Color::SkyBlue))
        .setLayoutWeight<StackContainer>(1);
    container->addChild(rightContainer);
    auto rightImage = std::make_shared<Img>(imgTexture2 , imageSizeWidth,imageSizeHeight);
    rightImage->setLayoutGravity<Img>(LayoutGravity::Center)
        .setPadding<Img>(5,5,5,5)
        .setScaleMode<Img>(ImgScale::Mode::CenterInside)
        .setBackgroundColor<Img>(ConverColorValue(Color::Pink));
    rightContainer->addChild(rightImage);

    ui->setRootContainer(container);
}

void TestImgUi::onTick(){
    if(ui != nullptr){
        ui->startRenderUI();
    }
}

void TestImgUi::onDispose(){
    purple::Log::i("TestImgUi","TestImgUi::onDispose");
    if(bgm != nullptr){
        purple::AudioManager::getInstance()->releaseAudioEntity(bgm);
    }

     if(bgm2 != nullptr){
        purple::AudioManager::getInstance()->releaseAudioEntity(bgm);
    }
}

