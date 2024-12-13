//
// 用户输入
//
#pragma once

#include <memory>
#include <mutex>
#include <functional>
#include <map>
#include <algorithm>
#include <string>

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

    typedef std::function<void(InputEvent&)> OnEventCallback;

    class InputManager{
    public:
        InputManager(const InputManager&) = delete;
        InputManager& operator=(const InputManager&) = delete;    

        static std::unique_ptr<InputManager>& getInstance();

        InputManager();
        ~InputManager();

        void onEvent(InputEvent &event);

        void addEventListener(std::string callbackId, OnEventCallback callback);

        void removeEventListener(std::string callbackId);

        int getEventListenCallbackCount();

        void clearCallback();

    private:
        static std::mutex mtx;
        static std::unique_ptr<InputManager> instance_;

        bool isKeyBoardPressed = false;

        std::map<std::string, OnEventCallback> onEventCallbacks;
    };//end class InputManager
}

