#pragma once

#include <string>
#include <memory>
#include <functional>
#include <vector>
#include "glm/vec4.hpp"

namespace purple{
    class ContainerWidget;

    class ViewWidget{
    protected:
        int left = 0;
        int top = 0;
        int width = 0;
        int height = 0;

        glm::vec4 backgroundColor_;

        ContainerWidget *parentView_ = nullptr;
    public:
        void setWidth(int width);
        void setHeight(int height);

        virtual void onMeasure(int w , int h);

        virtual void onRender();
    };

    class ContainerWidget : public ViewWidget{
    public:
        virtual void onRender() override;
        virtual void onLayoutChild();
    private:
        std::vector<std::shared_ptr<ViewWidget>> children;
    };
    
    typedef std::function<std::shared_ptr<ContainerWidget> (void)> RenderBlock;
    typedef std::function<void (void)> ChildWidgetBlock;

    std::shared_ptr<ContainerWidget> Container(ChildWidgetBlock block);
    
    class TextureInfo;
    class UiRoot{
    public:
        UiRoot(int w, int h);

        ~UiRoot();

        void renderUi();

        void build(RenderBlock block);
    private:
        int rootWidth_;
        int rootHeight_;
        std::shared_ptr<TextureInfo> textureInfo_ = nullptr;
    };//end class
}
