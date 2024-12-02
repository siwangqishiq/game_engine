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
    auto container = std::make_shared<Container>(100,200);
    uiRoot->setRootContainer(container);

    uiRoot->startRenderUI();

    // EXPECT_EQ(100, container->getWidth());
    // EXPECT_EQ(200, container->getHeight());
    // EXPECT_EQ(0, container->left);
    // EXPECT_EQ(screenHeight, container->top);
}







