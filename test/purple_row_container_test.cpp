#include <gtest/gtest.h>
#include "purple.h"
#include "purple_ui.h"

class PurpleUiRowContainerTest : public ::testing::Test{
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

TEST_F(PurpleUiRowContainerTest,row_container_test_init){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto rootContainer = std::make_shared<Container>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(rootContainer);

    auto container = std::make_shared<RowContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    rootContainer->addChild(container);

    uiRoot->startRenderUI();

    EXPECT_EQ(purple::Engine::ScreenWidth , container->getWidth());
    EXPECT_EQ(purple::Engine::ScreenHeight , container->getHeight());
}

TEST_F(PurpleUiRowContainerTest,row_container_test_init2){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto rootContainer = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(rootContainer);

    auto container = std::make_shared<RowContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    container->setLayoutGravity<RowContainer>(LayoutGravity::TopLeft);
    rootContainer->addChild(container);

    uiRoot->startRenderUI();

    EXPECT_EQ(purple::Engine::ScreenWidth , container->getWidth());
    EXPECT_EQ(purple::Engine::ScreenHeight , container->getHeight());
    EXPECT_EQ(0 , container->left);
    EXPECT_EQ(purple::Engine::ScreenHeight , container->top);
}

TEST_F(PurpleUiRowContainerTest,row_container_test_wrap){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth, 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto rootContainer = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(rootContainer);

    auto container = std::make_shared<RowContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    container->setLayoutGravity<RowContainer>(LayoutGravity::TopLeft);
    rootContainer->addChild(container);

    auto child1 = std::make_shared<Widget>(100,200);
    container->addChild(child1);

    auto child2 = std::make_shared<Widget>(200,100);
    container->addChild(child2);

    auto child3 = std::make_shared<Widget>(100,300);
    container->addChild(child3);

    uiRoot->startRenderUI();

    EXPECT_EQ(300 , container->getHeight());
    EXPECT_EQ(100 + 200 + 100 , container->getWidth());
}

TEST_F(PurpleUiRowContainerTest,row_container_test_wrap_with_padding){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth, 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto rootContainer = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(rootContainer);

    auto container = std::make_shared<RowContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    container->setLayoutGravity<RowContainer>(LayoutGravity::TopLeft);
    container->setPadding<RowContainer>(10,10,10,10);
    rootContainer->addChild(container);

    auto child1 = std::make_shared<Widget>(100,200);
    container->addChild(child1);

    auto child2 = std::make_shared<Widget>(200,100);
    container->addChild(child2);

    auto child3 = std::make_shared<Widget>(100,300);
    container->addChild(child3);

    uiRoot->startRenderUI();

    EXPECT_EQ(300 + 20 , container->getHeight());
    EXPECT_EQ(100 + 200 + 100 + 20 , container->getWidth());
}

TEST_F(PurpleUiRowContainerTest,row_container_test_wrap_with_margin){
    using namespace purple;

    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth, 
        purple::Engine::ScreenHeight
    );

    auto rootContainer = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(rootContainer);

    auto container = std::make_shared<RowContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    container->setLayoutGravity<RowContainer>(LayoutGravity::TopLeft);
    rootContainer->addChild(container);

    auto child1 = std::make_shared<Widget>(100,200);
    child1->setMargin<Widget>(10, 20, 10,20);
    container->addChild(child1);

    auto child2 = std::make_shared<Widget>(200,100);
    container->addChild(child2);

    auto child3 = std::make_shared<Widget>(100,300);
    child3->setMargin<Widget>(0, 20, 0,40);
    container->addChild(child3);

    uiRoot->startRenderUI();

    EXPECT_EQ(300 + 20 + 40, container->getHeight());
    EXPECT_EQ(100 + 10 + 10 + 200 + 100, container->getWidth());
}

TEST_F(PurpleUiRowContainerTest,row_container_test_wrap_stack_child){
    using namespace purple;
    
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth, 
        purple::Engine::ScreenHeight
    );

    auto rootContainer = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(rootContainer);

    auto container = std::make_shared<RowContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    container->setLayoutGravity<RowContainer>(LayoutGravity::TopLeft);
    rootContainer->addChild(container);

    auto childContainer = std::make_shared<StackContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    container->addChild(childContainer);

    auto child1 = std::make_shared<Widget>(100,300);
    child1->setMargin<Widget>(10, 20, 10,20)
        .setLayoutGravity<Widget>(LayoutGravity::Center);
    childContainer->addChild(child1);

    auto child2 = std::make_shared<Widget>(200,100);
    container->addChild(child2);

    auto child3 = std::make_shared<Widget>(100,300);
    container->addChild(child3);

    uiRoot->startRenderUI();

    EXPECT_EQ(300 + 20 + 20, container->getHeight());
    EXPECT_EQ(120 + 200 + 100, container->getWidth());
}

TEST_F(PurpleUiRowContainerTest,row_container_test_wrap_colum_child){
    using namespace purple;
    
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth, 
        purple::Engine::ScreenHeight
    );

    auto rootContainer = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(rootContainer);

    auto container = std::make_shared<RowContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    container->setLayoutGravity<RowContainer>(LayoutGravity::TopLeft);
    rootContainer->addChild(container);

    auto childContainer = std::make_shared<ColumContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    container->addChild(childContainer);

    auto child1 = std::make_shared<Widget>(100,300);
    childContainer->addChild(child1);
    auto child2 = std::make_shared<Widget>(100,300);
    childContainer->addChild(child2);

    auto child3 = std::make_shared<Widget>(100,300);
    container->addChild(child3);

    auto child4 = std::make_shared<Widget>(100,300);
    container->addChild(child3);

    uiRoot->startRenderUI();

    EXPECT_EQ(600, container->getHeight());
    EXPECT_EQ(300, container->getWidth());
}

TEST_F(PurpleUiRowContainerTest,row_container_test_wrap_poisition){
    using namespace purple;
    
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth, 
        purple::Engine::ScreenHeight
    );

    auto rootContainer = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(rootContainer);

    auto container = std::make_shared<RowContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    container->setLayoutGravity<RowContainer>(LayoutGravity::TopLeft);
    rootContainer->addChild(container);

    auto child1 = std::make_shared<Widget>(100,300);
    container->addChild(child1);

    auto child2 = std::make_shared<Widget>(200,100);
    container->addChild(child2);

    auto child3 = std::make_shared<Widget>(100,300);
    container->addChild(child3);

    uiRoot->startRenderUI();

    EXPECT_EQ(0, container->getLeft());
    EXPECT_EQ(purple::Engine::ScreenHeight, container->getTop());
    EXPECT_EQ(child1->left , container->getLeft());
    EXPECT_EQ(child1->top , container->getTop());

    EXPECT_EQ(child2->left , container->getLeft() + child1->getWidth());
    EXPECT_EQ(child2->top , container->getTop());

    EXPECT_EQ(child3->left , container->getLeft() + child1->getWidth() + child2->getWidth());
    EXPECT_EQ(child3->top , container->getTop());
}


TEST_F(PurpleUiRowContainerTest,row_container_test_poisition_with_margin){
    using namespace purple;
    
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth, 
        purple::Engine::ScreenHeight
    );

    auto rootContainer = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(rootContainer);

    auto container = std::make_shared<RowContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    container->setLayoutGravity<RowContainer>(LayoutGravity::TopLeft);
    rootContainer->addChild(container);

    auto child1 = std::make_shared<Widget>(100,300);
    child1->setMargin<Widget>(10,20,10,0);
    container->addChild(child1);

    auto child2 = std::make_shared<Widget>(200,100);
    container->addChild(child2);

    auto child3 = std::make_shared<Widget>(100,300);
    container->addChild(child3);

    uiRoot->startRenderUI();

    EXPECT_EQ(0, container->getLeft());
    EXPECT_EQ(purple::Engine::ScreenHeight, container->getTop());
    EXPECT_EQ(child1->left , container->getLeft() + 10);
    EXPECT_EQ(child1->top , container->getTop() - 20);

    EXPECT_EQ(child2->left , container->getLeft() + child1->getWidth() + 20);
    EXPECT_EQ(child2->top , container->getTop());

    EXPECT_EQ(child3->left , container->getLeft() + child1->getWidth() + child2->getWidth() + 20);
    EXPECT_EQ(child3->top , container->getTop());
}

