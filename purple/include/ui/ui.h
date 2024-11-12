#pragma once

#include <string>
#include <memory>
#include <functional>
#include <vector>
#include "glm/vec4.hpp"
#include "log.h"

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

        void setParentWidget(Container *parent);
        Widget& setBackgroundColor(glm::vec4 color);

        int left = 0;
        int top = 0;

        std::string id;

        Widget& setSize(int requestW,int requestH);
    protected:
        Container *parent_ = nullptr;
        glm::vec4 bgColor_;


        int requestWidth_;
        int requestHeight_;

        int width_ = 0;
        int height_ = 0;
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
