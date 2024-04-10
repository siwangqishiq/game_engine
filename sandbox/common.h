#pragma once

class IApp{
public:
    virtual void onInit() = 0;
    virtual void onTick() = 0;
    virtual void onDispose() = 0;
    virtual void onEvent(){}
};