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

    bool UiRoot::dispatchInputEvent(InputEvent &event){
        // Log::i("ui" , "event %d , %f %f" , event.action , event.x , event.y);
        if(rootContainer_ == nullptr){
            return false;
        }

        if(targetWidget != nullptr){
            return targetWidget->onInputEvent(event);
        }

        return false;
    }

    void UiRoot::measure(){
        // Log::i("widget" , "UiRoot start measure");
        if(this->rootContainer_ == nullptr){
            return;
        }

        int reqW = this->rootContainer_->getRequestWidth();
        MeasureSpecMode wMode = MeasureSpecMode::Unset;
        int widthValue = 0;
        if(reqW == LAYOUT_MATCH_PARENT){
            wMode = MeasureSpecMode::Exactly;
            widthValue = this->rootWidth_;
        }else if(reqW == LAYOUT_WRAP_CONTENT){
            wMode = MeasureSpecMode::Atmost;
            widthValue = this->rootWidth_;
        }else {
            wMode = MeasureSpecMode::Exactly;
            widthValue = reqW;
        }

        int reqH = this->rootContainer_->getRequestHeight();
        MeasureSpecMode hMode = MeasureSpecMode::Unset;
        int heightValue = 0;
        if(reqH == LAYOUT_MATCH_PARENT){
            hMode = MeasureSpecMode::Exactly;
            heightValue = this->rootHeight_;
        }else if(reqH == LAYOUT_WRAP_CONTENT){
            hMode = MeasureSpecMode::Atmost;
            heightValue = this->rootHeight_;
        }else {
            hMode = MeasureSpecMode::Exactly;
            heightValue = reqH;
        }

        this->rootContainer_->measure(wMode, widthValue, hMode, heightValue);
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
        if(!purple::UNITTEST){
            render();
        }
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

    void Widget::onMeasure(MeasureSpecMode widthSpecMode, 
                                int widthValue, 
                                MeasureSpecMode heightSpecMode,
                                int heightValue){
        // std::cout << "Widget::onMeasure" << std::endl;
        if(widthSpecMode == MeasureSpecMode::Exactly){
            setWidth(widthValue);
        }else if(widthSpecMode == MeasureSpecMode::Atmost){
            setWidth(std::min(paddingLeft_ + contentWidth() + paddingRight_, widthValue));
        }else if(widthSpecMode == MeasureSpecMode::Unset){
            setWidth(0);
        }

        if(heightSpecMode == MeasureSpecMode::Exactly){
            setHeight(heightValue);
        }else if(heightSpecMode == MeasureSpecMode::Atmost){
            setHeight(std::min(paddingTop_ + contentHeight() + paddingBottom_, heightValue));
        }else if(heightSpecMode == MeasureSpecMode::Unset){
            setHeight(0);
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

    void Widget::measure(MeasureSpecMode widthSpecMode, 
                        int widthValue, 
                        MeasureSpecMode heightSpecMode,
                        int heightValue) {
        if(visible_ == Gone){
            return;
        }

        onMeasure(widthSpecMode , widthValue, heightSpecMode , heightValue);
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

    Rect Widget::getWidgetRect(){
        const int l = this->left;
        const int t = this->top;
        const int w = this->width_;
        const int h = this->height_;
        return Rect(l, t, w ,h);
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

    PWidget FunContainer(std::vector<PWidget> children){
        std::shared_ptr<Container> container = std::make_shared<Container>();

        //set container
        
        return container;
    }

    bool Widget::onInputEvent(InputEvent &event){
        return false;
    }

    bool Widget::dispatchInputEvent(InputEvent &event){
        return onInputEvent(event);
    }
}

