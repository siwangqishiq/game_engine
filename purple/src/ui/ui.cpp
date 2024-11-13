#include "ui/ui.h"
#include "log.h"
#include "purple.h"
#include "algorithm"

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

    void UiRoot::measure(){
        // Log::i("widget" , "UiRoot start measure");
        if(this->rootContainer_ == nullptr){
            return;
        }

        this->rootContainer_->measure(this->rootWidth_ , this->rootHeight_);
    }
    
    void UiRoot::layout(){
        // Log::i("widget" , "UiRoot start layout");
        if(this->rootContainer_ == nullptr){
            return;
        }

        this->rootContainer_->layout(0 , this->rootHeight_);
    }
    
    void UiRoot::render(){
        // Log::i("widget" , "UiRoot start render");
        if(this->rootContainer_ == nullptr){
            return;
        }

        this->rootContainer_->render();
    }

    void UiRoot::startRenderUI(){
        measure();
        layout();
        render();
    }

    //===============================================================================
    //================================================================================

    // Widget::Widget(int w, int h){
    //     this->width = w;
    //     this->height = h;
    //     Log::i("widget","widget construct");
    // }

    void Widget::setParentWidget(Container *parent){
        this->parent_ = parent;
    }

    // Widget& Widget::setSize(int requestW,int requestH){
    //     this->requestWidth_ = requestW;
    //     this->requestHeight_ = requestH;
    //     return *this;
    // }

    // Widget& Widget::setBackgroundColor(glm::vec4 color){
    //     this->bgColor_ = color;
    //     return *this;
    // }

    void Widget::measure(int parentRequestWidth , int parentRequestHeight){
        if(this->requestWidth_ == LAYOUT_MATCH_PARENT){
            this->width_ = parentRequestWidth;
        }else if(this->requestWidth_ == LAYOUT_WRAP_CONTENT){
            
        }else{
            this->width_ = this->requestWidth_;
        }

        if(this->requestHeight_ == LAYOUT_MATCH_PARENT){
            this->height_ = parentRequestHeight;
        }else if(this->requestHeight_ == LAYOUT_WRAP_CONTENT){

        }else{
            this->height_ = this->requestHeight_;
        }
    }

    void Widget::layout(int l,int t){
        this->left = l;
        this->top = t;
    }

    void Widget::render(){
        // Log::e("render" , "render %d %d %d %d",this->left , this->top , this->width , this->height);

        Rect bgRect(this->left , this->top , this->width_ , this->height_);
        Paint bgPaint;
        bgPaint.color = this->bgColor_;

        auto render = purple::Engine::getRenderEngine();
        auto shapeBatch = render->getShapeBatch();
        shapeBatch->begin();
        shapeBatch->renderRect(bgRect, bgPaint);
        shapeBatch->end();
    }

    Widget::~Widget(){
        Log::i("widget","widget desstory");
    }

    Container::~Container(){
        this->Widget::~Widget();
    }

    void Container::addChild(PWidget widget){
        this->children_.push_back(widget);
        widget->setParentWidget(this);
    }

    void Container::removeChild(PWidget widget){
        widget->setParentWidget(nullptr);
        this->children_.erase(std::find(this->children_.begin(),this->children_.end(),widget));
    }

    void Container::measure(int parentRequestWidth , int parentRequestHeight){
        //set self width and height
        this->Widget::measure(parentRequestWidth, parentRequestHeight);
        
        //set child measure
        if(this->children_.empty()){
            return;
        }

        for(auto &child: this->getChildrenWidgets()){
            child->measure(this->width_ , this->height_);
        }//end for each
    }

    void Container::layout(int l,int t){
        this->Widget::layout(l,t);
        //Container绝对布局 不需要设置子Widget位置
    }

    void Container::render(){
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
        this->Widget::render();
    }

    std::vector<PWidget> Container::getChildrenWidgets(){
        return this->children_;
    }

    PWidget FunContainer(std::vector<PWidget> children){
        std::shared_ptr<Container> container = std::make_shared<Container>();

        //set container
        
        return container;
    }


}

