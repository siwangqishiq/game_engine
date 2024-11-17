

#include "ui/row_container.h"

namespace purple{

    void RowContainer::measure(int parentRequestWidth , int parentRequestHeight) {
        int maxWidgetHeight = 0;
        int totalWidgetWidth = 0;
        const auto childWidgets = getChildrenWidgets();
        std::vector<PWidget> hasWeightWidgetList;

        int costWidthSize = paddingLeft_ + paddingRight_;
        for(auto widget: childWidgets){
            if(widget == nullptr){
                continue;
            }

            widget->measure(parentRequestWidth , parentRequestHeight);
            if(widget->getLayoutWeight() > 0){
                hasWeightWidgetList.emplace_back(widget);
                costWidthSize += widget->getMarginLeft() + widget->getMarginRight();
            }else{
                costWidthSize += widget->getMarginLeft() + widget->getWidth() + widget->getMarginRight();
            }

            totalWidgetWidth += widget->getMarginLeft() + widget->getMarginRight() + widget->getWidth();
            if(maxWidgetHeight < widget->getHeight()){
                maxWidgetHeight = widget->getHeight();
            }
        }//end for each


        //set width
        if(this->requestWidth_ == LAYOUT_MATCH_PARENT){
            this->width_ = parentRequestWidth;
        }else if(this->requestWidth_ == LAYOUT_WRAP_CONTENT){
            if(hasWeightWidgetList.empty()){
                this->width_ = totalWidgetWidth + paddingLeft_ + paddingRight_;
            }else{
                this->width_ = parentRequestWidth;
            }
        }else {
            this->width_ = this->requestWidth_;
        }//endif

        if(!hasWeightWidgetList.empty()){ //存在weight属性 重置关联widget width
            int totalWeightValue = 0;
            for(auto &widget: hasWeightWidgetList){
                totalWeightValue += widget->getLayoutWeight();
            }//end for each

            const int cubeSize =  static_cast<int>(
                static_cast<float>(this->width_ - costWidthSize) / static_cast<float>(totalWeightValue)
            );

            for(auto &widget: hasWeightWidgetList){
                widget->setWidth(cubeSize * widget->getLayoutWeight());
            }
        }//end if

        //set height
        if(this->requestHeight_ == LAYOUT_MATCH_PARENT){
            this->height_ = parentRequestHeight;
        }else if(this->requestHeight_ == LAYOUT_WRAP_CONTENT){
            this->height_ = maxWidgetHeight + paddingTop_ + paddingBottom_;
        }else {
            this->height_ = this->requestHeight_;
        }//end if


    }

    void RowContainer::layout(int l,int t) {
        this->Container::layout(l , t);

        int x = paddingLeft_ + left;
        int y = top - paddingTop_;

        for(auto widget: getChildrenWidgets()){
            if(widget == nullptr){
                continue;
            }
            
            const LayoutGravity gravity = widget->getLayoutGravity();
            if(gravity == LayoutGravity::TopCenter
                || gravity == LayoutGravity::TopLeft
                || gravity == LayoutGravity::TopRight){ // top
                y = top - paddingTop_;
            }else if(gravity == LayoutGravity::CenterLeft 
                || gravity == LayoutGravity::Center 
                || gravity == LayoutGravity::CenterRight){ // center
                y = top - (this->height_ >> 1) +(widget->getHeight() >> 1);
            }else{ //bottom
                y = top - this->height_ + widget->getHeight();
            }//end if
            
            widget->layout(x + widget->getMarginLeft() , y - widget->getMarginTop()); 
            x += widget->getMarginLeft() + widget->getMarginRight() + widget->getWidth();
        }//end for each
    }


    RowContainer::~RowContainer(){
        
    }
}