#include <gtest/gtest.h>
#include "purple.h"
#include "purple_ui.h"


class PurpleUiTest : public ::testing::Test{
public:
    const int screenWidth = 1280;
    const int screenHeight = 800;
    std::shared_ptr<purple::UiRoot> uiRoot = nullptr;
    
protected:
    void SetUp() override {
        purple::UNITTEST = true;
        purple::Engine::init(screenWidth , screenHeight);   
    }

    void TearDown() override {
        uiRoot = nullptr;
        purple::Engine::dispose();
    }
};

TEST_F(PurpleUiTest, purple_init) {
    EXPECT_EQ(purple::Engine::ScreenWidth , screenWidth);
    EXPECT_EQ(purple::Engine::ScreenHeight , screenHeight);
}

TEST_F(PurpleUiTest,rootview_init){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<Container>(100,200);
    uiRoot->setRootContainer(container);

    uiRoot->startRenderUI();

    EXPECT_EQ(100, container->getWidth());
    EXPECT_EQ(200, container->getHeight());
    EXPECT_EQ(0, container->left);
    EXPECT_EQ(screenHeight, container->top);
}


TEST_F(PurpleUiTest,rootview_init_visible_set_gone){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<Container>(100,200);
    uiRoot->setRootContainer(container);
    container->setVisible(VisibleState::Gone);

    uiRoot->startRenderUI();

    EXPECT_EQ(0, container->getWidth());
    EXPECT_EQ(0, container->getHeight());
}

TEST_F(PurpleUiTest,rootview_init_visible_set_invisible){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<Container>(100,200);
    uiRoot->setRootContainer(container);
    container->setVisible(VisibleState::InVisible);

    uiRoot->startRenderUI();

    EXPECT_EQ(100, container->getWidth());
    EXPECT_EQ(200, container->getHeight());
}

TEST_F(PurpleUiTest,rootview_container_match_parent){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<Container>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    uiRoot->startRenderUI();

    EXPECT_EQ(screenWidth, container->getWidth());
    EXPECT_EQ(screenHeight, container->getHeight());
    EXPECT_EQ(0, container->left);
    EXPECT_EQ(screenHeight, container->top);
}

TEST_F(PurpleUiTest,rootview_container_layout){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<Container>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);
    auto childContainer = std::make_shared<Container>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    
    container->addChild(childContainer);

    childContainer->left = 20;
    childContainer->top = 100;

    uiRoot->startRenderUI();

    EXPECT_EQ(screenWidth, container->getWidth());
    EXPECT_EQ(screenHeight, container->getHeight());

    EXPECT_EQ(20, childContainer->left);
    EXPECT_EQ(100, childContainer->top);

    EXPECT_EQ(container->getWidth(), childContainer->getWidth());
    EXPECT_EQ(container->getHeight(), childContainer->getHeight());
}






