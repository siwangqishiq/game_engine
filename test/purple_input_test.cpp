#include <gtest/gtest.h>
#include "purple.h"
#include "input/input_manager.h"
#include "purple_ui.h"

class PurpleInputTest : public ::testing::Test{
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

TEST_F(PurpleInputTest,input_manager_init){
    using namespace purple;
    EXPECT_TRUE(InputManager::getInstance() != nullptr);
}

TEST_F(PurpleInputTest,input_manager_update_callback){
    using namespace purple;
    auto cb1 = [](InputEvent &e){};
    auto cb2 = [](InputEvent &e){};
    InputManager::getInstance()->addEventListener("cb1", cb1);
    InputManager::getInstance()->addEventListener("cb2", cb2);
    InputManager::getInstance()->addEventListener("cb2", cb2);

    EXPECT_EQ(2 , InputManager::getInstance()->getEventListenCallbackCount());
}

TEST_F(PurpleInputTest,input_manager_remove_callback){
    using namespace purple;
    auto cb1 = [](InputEvent &e){};
    auto cb2 = [](InputEvent &e){};
    InputManager::getInstance()->addEventListener("cb1", cb1);
    InputManager::getInstance()->addEventListener("cb2", cb2);
    InputManager::getInstance()->addEventListener("cb2", cb2);

    InputManager::getInstance()->removeEventListener("cb1");
    EXPECT_EQ(1 , InputManager::getInstance()->getEventListenCallbackCount());
}

TEST_F(PurpleInputTest,input_manager_run_callback){
    using namespace purple;
    int counter = 0;

    auto cb1 = [&counter](InputEvent &e){
        counter++;
    };
    auto cb2 = [&counter](InputEvent &e){
        counter--;
    };

    InputManager::getInstance()->addEventListener("cb1", cb1);
    InputManager::getInstance()->addEventListener("cb2", cb2);

    EXPECT_EQ(2 , InputManager::getInstance()->getEventListenCallbackCount());

    InputEvent event;
    event.action = EVENT_ACTION_BEGIN;
    InputManager::getInstance()->onEvent(event);

    EXPECT_EQ(0 , counter);
}






