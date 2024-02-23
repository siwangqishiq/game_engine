
#include "purple.h"
#include "log.h"

#include <stdio.h>

namespace purple{
    void Engine::init(int width , int height){
        Log::w(TAG,"init engine");
        ScreenWidth = width;
        ScreenHeight = height;

        Log::w(TAG,"init screen size: %d  , %d" , ScreenWidth , ScreenHeight);
    }

    void Engine::dispose(){
        Log::w(TAG,"engine dispose");
    }
}