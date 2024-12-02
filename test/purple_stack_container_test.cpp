#include <gtest/gtest.h>
#include "purple.h"
#include "purple_ui.h"

const int screenWidth = 1280;
const int screenHeight = 800;

class PurpleStackContainerTest : public ::testing::Test{
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

TEST_F(PurpleStackContainerTest, stack_container_self_size){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<StackContainer>(100,200);
    uiRoot->setRootContainer(container);

    uiRoot->startRenderUI();

    EXPECT_EQ(100, container->getWidth());
    EXPECT_EQ(200, container->getHeight());
}

TEST_F(PurpleStackContainerTest, stack_container_match_parent){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    uiRoot->startRenderUI();

    EXPECT_EQ(purple::Engine::ScreenWidth, container->getWidth());
    EXPECT_EQ(purple::Engine::ScreenHeight, container->getHeight());
}

TEST_F(PurpleStackContainerTest, stack_container_add_child){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    auto child = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    container->addChild(child);

    uiRoot->startRenderUI();

    EXPECT_EQ(container->getWidth(), child->getWidth());
    EXPECT_EQ(container->getHeight(), child->getHeight());

    EXPECT_EQ(container->left, child->left);
    EXPECT_EQ(container->top, child->top);
}

TEST_F(PurpleStackContainerTest, stack_container_add_child_wrapcontent){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    auto child = std::make_shared<StackContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    child->setRequestWidth(123);
    child->setRequestHeight(321);

    container->addChild(child);

    uiRoot->startRenderUI();

    EXPECT_EQ(123, child->getWidth());
    EXPECT_EQ(321, child->getHeight());

    EXPECT_EQ(container->left, child->left);
    EXPECT_EQ(container->top, child->top);
}

TEST_F(PurpleStackContainerTest, stack_container_add_child_layout_top_left){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    const int childWidth = 100;
    const int childHeight = 200;
    auto child = std::make_shared<StackContainer>(childWidth,childHeight);
    child->setLayoutGravity<Widget>(LayoutGravity::TopLeft);

    container->addChild(child);
    uiRoot->startRenderUI();

    EXPECT_EQ(childWidth, child->getWidth());
    EXPECT_EQ(childHeight, child->getHeight());

    EXPECT_EQ(container->left, child->left);
    EXPECT_EQ(container->top, child->top);
}

TEST_F(PurpleStackContainerTest, stack_container_add_child_layout_top_center){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    const int childWidth = 100;
    const int childHeight = 200;
    auto child = std::make_shared<StackContainer>(childWidth,childHeight);
    child->setLayoutGravity<Widget>(LayoutGravity::TopCenter);

    container->addChild(child);
    uiRoot->startRenderUI();

    EXPECT_EQ(childWidth, child->getWidth());
    EXPECT_EQ(childHeight, child->getHeight());

    EXPECT_EQ(container->top, child->top);
    EXPECT_EQ(container->left + container->getWidth() / 2.0f - child->getWidth() / 2.0f, 
        child->left);
}

TEST_F(PurpleStackContainerTest, stack_container_add_child_layout_top_right){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    const int childWidth = 100;
    const int childHeight = 200;
    auto child = std::make_shared<StackContainer>(childWidth,childHeight);
    child->setLayoutGravity<Widget>(LayoutGravity::TopRight);

    container->addChild(child);
    uiRoot->startRenderUI();

    EXPECT_EQ(childWidth, child->getWidth());
    EXPECT_EQ(childHeight, child->getHeight());

    EXPECT_EQ(container->top, child->top);
    EXPECT_EQ(container->left + container->getWidth() - child->getWidth(), 
        child->left);
}

TEST_F(PurpleStackContainerTest, stack_container_add_child_layout_center_left){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    const int childWidth = 100;
    const int childHeight = 200;
    auto child = std::make_shared<StackContainer>(childWidth,childHeight);
    child->setLayoutGravity<Widget>(LayoutGravity::CenterLeft);

    container->addChild(child);
    uiRoot->startRenderUI();

    EXPECT_EQ(childWidth, child->getWidth());
    EXPECT_EQ(childHeight, child->getHeight());

    EXPECT_EQ(container->left, child->left);
    EXPECT_EQ(container->top - container->getHeight()/ 2.0f + child->getHeight() / 2.0f, 
        child->top);
}

TEST_F(PurpleStackContainerTest, stack_container_add_child_layout_center_center){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    const int childWidth = 100;
    const int childHeight = 200;
    auto child = std::make_shared<StackContainer>(childWidth,childHeight);
    child->setLayoutGravity<Widget>(LayoutGravity::Center);

    container->addChild(child);
    uiRoot->startRenderUI();

    EXPECT_EQ(childWidth, child->getWidth());
    EXPECT_EQ(childHeight, child->getHeight());

    EXPECT_EQ(container->top - container->getHeight()/ 2.0f + child->getHeight() / 2.0f, 
        child->top);
    EXPECT_EQ(container->left + container->getWidth() / 2.0f - child->getWidth() / 2.0f, 
        child->left);
}

TEST_F(PurpleStackContainerTest, stack_container_add_child_layout_center_right){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    const int childWidth = 100;
    const int childHeight = 200;
    auto child = std::make_shared<StackContainer>(childWidth,childHeight);
    child->setLayoutGravity<Widget>(LayoutGravity::CenterRight);

    container->addChild(child);
    uiRoot->startRenderUI();

    EXPECT_EQ(childWidth, child->getWidth());
    EXPECT_EQ(childHeight, child->getHeight());

    EXPECT_EQ(container->top - container->getHeight()/ 2.0f + child->getHeight() / 2.0f, 
        child->top);
    EXPECT_EQ(container->left + container->getWidth() - child->getWidth(), 
        child->left);
}

TEST_F(PurpleStackContainerTest, stack_container_add_child_layout_bottom_left){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;

    const int padding = 20;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    container->setPadding<StackContainer>(padding,padding , padding , padding);
    uiRoot->setRootContainer(container);

    const int childWidth = 100;
    const int childHeight = 200;

    auto child = std::make_shared<StackContainer>(childWidth,childHeight);
    child->setLayoutGravity<Widget>(LayoutGravity::BottomLeft);

    container->addChild(child);
    uiRoot->startRenderUI();

    EXPECT_EQ(childWidth, child->getWidth());
    EXPECT_EQ(childHeight, child->getHeight());

    EXPECT_EQ(
        container->top - container->getHeight() + padding + child->getHeight(), 
        child->top);
    EXPECT_EQ(container->left + padding, child->left);
}

TEST_F(PurpleStackContainerTest, stack_container_add_child_layout_bottom_center){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;

    const int padding = 20;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    container->setPadding<StackContainer>(padding,padding , padding , padding);
    uiRoot->setRootContainer(container);

    const int childWidth = 100;
    const int childHeight = 200;

    auto child = std::make_shared<StackContainer>(childWidth,childHeight);
    child->setLayoutGravity<Widget>(LayoutGravity::BottomCenter);

    container->addChild(child);
    uiRoot->startRenderUI();

    EXPECT_EQ(childWidth, child->getWidth());
    EXPECT_EQ(childHeight, child->getHeight());

    EXPECT_EQ(
        container->top - container->getHeight() + padding + child->getHeight(), 
        child->top);
    EXPECT_EQ(container->left + container->getWidth() / 2.0f - child->getWidth() / 2.0f, 
        child->left);
}


TEST_F(PurpleStackContainerTest, stack_container_add_child_layout_bottom_right){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;

    const int padding = 20;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    container->setPadding<StackContainer>(padding,padding , padding , padding);
    uiRoot->setRootContainer(container);

    const int childWidth = 100;
    const int childHeight = 200;

    auto child = std::make_shared<StackContainer>(childWidth,childHeight);
    child->setLayoutGravity<Widget>(LayoutGravity::BottomRight);

    container->addChild(child);
    uiRoot->startRenderUI();

    EXPECT_EQ(childWidth, child->getWidth());
    EXPECT_EQ(childHeight, child->getHeight());

    EXPECT_EQ(
        container->top - container->getHeight() + padding + child->getHeight(), 
        child->top);

    EXPECT_EQ(container->left + container->getWidth()  - child->getWidth() - padding, 
        child->left);
}


