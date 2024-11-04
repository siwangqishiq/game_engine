#include "ui/ui.h"
#include "log.h"

namespace purple{

    UiRoot::UiRoot(int w, int h) {
        this->rootWidth_ = w;
        this->rootHeight_ = h;
        Log::i("ui", "UiRoot create width:%d, height:%d"
            ,this->rootWidth_
            ,this->rootHeight_);
    }

    UiRoot::~UiRoot(){
        Log::i("ui", "UiRoot destoryed");
    }


    void UiRoot::build(RenderBlock block){
        // widget --> render command

    }

     void UiRoot::renderUi(){
        Log::i("ui", "UiRoot begin renderUI...");

     }


    void ViewWidget::setWidth(int width){
        this->width = width;
    }
    void ViewWidget::setHeight(int height){
        this->height = height;
    }

    void ViewWidget::onRender(){
        
    }

    void ViewWidget::onMeasure(int w , int h){

    }

    void ContainerWidget::onRender(){

    }
    
    void ContainerWidget::onLayoutChild(){
        
    }

    std::shared_ptr<ContainerWidget> Container(ChildWidgetBlock block){
        auto container = std::make_shared<ContainerWidget>();
        return container;
    }
}

