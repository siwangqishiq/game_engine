#include "ui/ui.h"
#include "log.h"
#include "purple.h"
#include "algorithm"
#include "ui/color.h"

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

    void UiRoot::setRootContainer(PContainer container){
        this->rootContainer_ = container;
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

    void Widget::setParentWidget(Container *parent){
        this->parent_ = parent;
    }


    int Widget::contentWidth(){
        return 0;
    }

    int Widget::contentHeight(){
        return 0;
    }

    void Widget::onMeasure(int parentRequestWidth , int parentRequestHeight){
        if(requestWidth_ == LAYOUT_MATCH_PARENT){
            width_ = parentRequestWidth;
        }else if(this->requestWidth_ == LAYOUT_WRAP_CONTENT){
            width_ = std::min(paddingLeft_ + contentWidth() + paddingRight_, parentRequestWidth);
        }else{
            width_ = requestWidth_;
        }

        if(this->requestHeight_ == LAYOUT_MATCH_PARENT){
            height_ = parentRequestHeight;
        }else if(this->requestHeight_ == LAYOUT_WRAP_CONTENT){
            height_ = std::min(paddingTop_ + contentHeight() + paddingBottom_, parentRequestHeight);
        }else{
            height_ = requestHeight_;
        }
    }

    void Widget::onLayout(int l,int t){
        this->left = l;
        this->top = t;
        // Log::w("test" , "widget id: %s pos: %d , %d" , this->id.c_str(), this->left , this->top);
    }

    void Widget::onRender(){
        // Log::e("render" , "render %d %d %d %d",this->left , this->top , this->width , this->height);
        if(this->bgColor_ == ConverColorValue(Color::Transparent)){
            return;
        }

        Rect bgRect(this->left , this->top , this->width_ , this->height_);
        Paint bgPaint;
        bgPaint.color = this->bgColor_;

        auto render = purple::Engine::getRenderEngine();
        auto shapeBatch = render->getShapeBatch();
        shapeBatch->begin();
        // shapeBatch->renderRect(bgRect, bgPaint);
        shapeBatch->renderRoundRect(bgRect, bgConnerRadius_ , bgPaint);
        shapeBatch->end();
    }

    Widget::~Widget(){
        // Log::i("widget","widget desstory");
    }

    Container::~Container(){
        // Log::i("widget","Container desstory");
    }

    void Widget::measure(int parentRequestWidth , int parentRequestHeight){
        if(visible_ == Gone){
            return;
        }

        onMeasure(parentRequestWidth, parentRequestHeight);
    }
    void Widget::layout(int l , int t){
        if(visible_ == Gone){
            return;
        }

        onLayout(l,t);
    }

    void Widget::render(){
        if(visible_ != Normal){
            return;
        }
        onRender();
    }

    void Container::addChild(PWidget widget){
        this->children_.push_back(widget);
        widget->setParentWidget(this);
    }

    void Container::removeChild(PWidget widget){
        widget->setParentWidget(nullptr);
        this->children_.erase(std::find(this->children_.begin(),this->children_.end(),widget));
    }

    void Container::onMeasure(int parentRequestWidth , int parentRequestHeight){
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

    void Container::onLayout(int l,int t){
        // Log::i("widget" , "Container start layout");
        this->Widget::onLayout(l,t);
        //Container绝对布局 不需要设置子Widget位置
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

    std::vector<PWidget>& Container::getChildrenWidgets(){
        return this->children_;
    }

    PWidget FunContainer(std::vector<PWidget> children){
        std::shared_ptr<Container> container = std::make_shared<Container>();

        //set container
        
        return container;
    }


}

