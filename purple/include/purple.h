
#pragma once

#include "log.h"

namespace purple{
    
    inline const char *TAG = "purple";
    inline int ScreenWidth;
    inline int ScreenHeight;

    class Engine{
    public:
        static void init(int width , int height);

        static void dispose();
    };
}

