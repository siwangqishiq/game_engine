//
// Created by panyi on 2024/4/28.
//
#pragma once

#include <vector>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class IApp;


class AndroidApplication{
public:
    void init();
    void tick();
    void dispose();
    void resize(int w , int h);
    void onTouchEvent(int action , float x , float y);


private:
    std::vector<std::shared_ptr<IApp>> appInstanceList;

    int width = 1280;
    int height = 800;


};
