#pragma once

#include <string>
#include <memory>
#include <functional>
#include <vector>
#include "glm/vec4.hpp"

namespace purple{
    const int LAYOUT_MATCH_PARENT = -1;
    const int LAYOUT_WRAP_CONTENT = -2;

    class Widget;
    class Container;

    typedef std::shared_ptr<Widget> PWidget;
    typedef std::shared_ptr<Container> PContainer;

   


    class Widget{
    public:
        Widget();
        virtual ~Widget();

        virtual void measure(int parentRequestWidth , int parentRequestHeight);
        virtual void layout(int l,int t);
        virtual void render();

        void setParentWidget(Container *parent);
        void setBackgroundColor(glm::vec4 color);

        int left = 0;
        int top = 0;
        int width = 0;
        int height = 0;
    protected:
        Container *parent_ = nullptr;
        glm::vec4 bgColor_;
    };//end class

    class Container:public Widget{
    public:
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

        ~UiRoot();
    private:
        int rootWidth_;
        int rootHeight_;
        std::shared_ptr<TextureInfo> textureInfo_ = nullptr;
        PContainer rootContainer_ = nullptr;
    };//end class
}
