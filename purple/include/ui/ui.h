#pragma once

#include <string>
#include <memory>
#include <functional>
#include <vector>
#include "glm/vec4.hpp"
#include "log.h"
#include "render/common.h"

namespace purple{
    const int LAYOUT_MATCH_PARENT = -1;
    const int LAYOUT_WRAP_CONTENT = -2;

    class Widget;
    class Container;

    typedef std::shared_ptr<Widget> PWidget;
    typedef std::shared_ptr<Container> PContainer;


    class Widget{
    public:
        Widget(){
            Log::i("widget","widget construct");
        }
        
        Widget(int w,int h):requestWidth_(w),requestHeight_(h){
            Log::i("widget","widget construct");
        }

        virtual ~Widget();

        virtual void measure(int parentRequestWidth , int parentRequestHeight);
        virtual void layout(int l,int t);
        virtual void render();

        virtual int contentWidth();
        virtual int contentHeight();

        void setParentWidget(Container *parent);

        int left = 0;
        int top = 0;

        std::string id;

        template<typename T>
        T& setBackgroundColor(glm::vec4 color){
            this->bgColor_ = color;
            return static_cast<T&>(*this);
        }

        template<typename T>
        T& setSize(int requestW,int requestH){
            this->requestWidth_ = requestW;
            this->requestHeight_ = requestH;
            return static_cast<T&>(*this);
        }

        template<typename T>
        T& setPadding(int paddingLeft,int paddingTop,int paddingRight, int paddingBottom){
            this->paddingLeft_ = paddingLeft;
            this->paddingTop_ = paddingTop;
            this->paddingRight_ = paddingRight;
            this->paddingBottom_ = paddingBottom;
            return static_cast<T&>(*this);
        }

        template<typename T>
        T& setBackgroundConnerRadius(float radius){
            this->bgConnerRadius_ = radius;
            return static_cast<T&>(*this);
        }

    protected:
        Container *parent_ = nullptr;

        glm::vec4 bgColor_;
        float bgConnerRadius_ = 0.0f;

        int requestWidth_;
        int requestHeight_;

        int width_ = 0;
        int height_ = 0;

        int paddingLeft_ = 0;
        int paddingRight_ = 0;
        int paddingTop_ = 0;
        int paddingBottom_ = 0;

        LayoutGravity layoutGravity_ = LayoutGravity::TopLeft;
    };//end class

    class Container:public Widget{
    public:
        Container():Widget(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT){
        }

        virtual ~Container();

        virtual void addChild(PWidget widget);
        virtual void removeChild(PWidget widget);

        virtual void measure(int parentRequestWidth , int parentRequestHeight);
        virtual void layout(int l,int t);
        virtual void render();

        void renderContainerSelf();

        std::vector<PWidget> getChildrenWidgets();
    protected:
        std::vector<PWidget> children_;
    };

    PWidget FunContainer(std::vector<PWidget> children);
    
    class TextureInfo;
    class UiRoot{
    public:
        UiRoot(int w, int h);
        
        void measure();
        void layout();
        void render();

        void startRenderUI();

        PContainer rootContainer_ = nullptr;

        ~UiRoot();
    private:
        int rootWidth_;
        int rootHeight_;
        std::shared_ptr<TextureInfo> textureInfo_ = nullptr;
        
    };//end class
}
