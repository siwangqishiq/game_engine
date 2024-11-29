#include <gtest/gtest.h>
#include "purple.h"
#include "purple_ui.h"

const int screenWidth = 1280;
const int screenHeight = 800;

void initPurple(){
    purple::UNITTEST = true;
    purple::Engine::init(screenWidth , screenHeight);   
}

void disposePurple(){
    purple::Engine::dispose();
}

TEST(PurpleUiTest, purple_init) {
    initPurple();
    EXPECT_EQ(purple::Engine::ScreenWidth , screenWidth);
    EXPECT_EQ(purple::Engine::ScreenHeight , screenHeight);
    disposePurple();
}

TEST(PurpleUiTest,Test){
    
}





