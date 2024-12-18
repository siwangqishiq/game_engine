#include "ui/container.h"

namespace purple{
    Container::~Container(){
        // Log::i("widget","Container desstory");
    }

    void Container::addChild(PWidget widget){
        this->children_.push_back(widget);
        widget->setParentWidget(this);
    }

    void Container::removeChild(PWidget widget){
        widget->setParentWidget(nullptr);
        this->children_.erase(std::find(this->children_.begin(),this->children_.end(),widget));
    }

    void Container::onMeasure(MeasureSpecMode widthSpecMode, 
                                int widthValue, 
                                MeasureSpecMode heightSpecMode,
                                int heightValue){
        //set self width and height
        this->Widget::onMeasure(widthSpecMode, widthValue, heightSpecMode, heightValue);
        
        //set child measure
        if(this->children_.empty()){
            return;
        }

        for(auto &child: this->getChildrenWidgets()){
            child->measure(widthSpecMode, this->width_ ,heightSpecMode, this->height_);
        }//end for each
    }

    void Container::onLayout(int l,int t){
        // Log::i("widget" , "Container start layout");
        this->Widget::onLayout(l,t);

        // if(this->children_.empty()){
        //     return;
        // }
        
        // for(auto &child: this->getChildrenWidgets()){
        // }//end for each
    }

    void Container::onRender(){
        if(visible_ == Gone || visible_ == InVisible){
            return;
        }

        this->renderContainerSelf();

        //set child measure
        if(this->children_.empty()){
            return;
        }

        for(auto &child: this->getChildrenWidgets()){
            child->render();
        }//end for each
    }

    void Container::renderContainerSelf(){
        // Log::e("widget" , "renderContainerSelf");
        this->Widget::onRender();
    }

    bool Container::dispatchInputEvent(InputEvent &event){
        if(visible_ != VisibleState::Normal){
            return false;
        }

        if(isInterceptInputEvent(event)){
            return onInputEvent(event);
        }else{
            for(auto &child : getChildrenWidgets()){
                if(child->dispatchInputEvent(event)){
                    return true;
                }
            }//end for each
            return false;
        }
    }

    bool Container::isInterceptInputEvent(InputEvent &event){
        return false;
    }

    std::vector<PWidget>& Container::getChildrenWidgets(){
        return this->children_;
    }
}
