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
    testImgScaleMode();
    
    // bgm = purple::AudioManager::getInstance()->loadAudioEntity("audio/jiangtiandao.mp3",true);
    // purple::AudioManager::getInstance()->setAudioPlayProgressCallback(bgm, [this](unsigned long progress , unsigned long total , double totalTime){
    //     double currentTime = (static_cast<double>(progress) / total) * totalTime;
    //     purple::Log::i("play_music","progress %lld / %lld  -- %f :%f" , progress  , total ,currentTime , totalTime);
    // });
    // purple::AudioManager::getInstance()->playAudioEntity(bgm);
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

void TestImgUi::onTick(){
    if(ui != nullptr){
        ui->startRenderUI();
    }
}

void TestImgUi::onDispose(){
    if(bgm != nullptr){
        purple::AudioManager::getInstance()->releaseAudioEntity(bgm);
    }
}

