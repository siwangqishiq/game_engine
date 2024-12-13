#pragma once

#include <iostream>

namespace purple{
    const int EVENT_ACTION_BEGIN = 1;
    const int EVENT_ACTION_MOVE = 2;
    const int EVENT_ACTION_END = 3;
    const int EVENT_ACTION_KEY = 10;//键盘按下事件

    struct InputEvent{
        int action;
        float x;
        float y;
        int code;
        void *ptrParam;
    };
}
