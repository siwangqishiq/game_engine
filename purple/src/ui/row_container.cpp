#include "ui/row_container.h"
#include <algorithm>

namespace purple{

    void RowContainer::onMeasure(int parentRequestWidth , int parentRequestHeight) {
        int maxWidgetHeight = 0;
        int totalWidgetWidth = 0;
        const auto childWidgets = getChildrenWidgets();
        std::vector<PWidget> hasWeightWidgetList;
        
        this->height_ = this->requestHeight_;
        if(this->requestHeight_ == LAYOUT_MATCH_PARENT){
            this->height_ = parentRequestHeight;
        }

        //set width
        if(this->requestWidth_ == LAYOUT_MATCH_PARENT){
            width_ = parentRequestWidth;
        }else {
            width_ = requestWidth_;
        }//endif

        int costWidthSize = paddingLeft_ + paddingRight_;
        for(auto widget: childWidgets){
            if(widget == nullptr || widget->getVisible() == Gone){
                continue;
            }

            widget->measure(width_ , height_);
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
                // Log::i("ui","widget %s set width = %d" , widget->id.c_str(), widget->getWidth());
            }
        }//end if

        
        //set width
        if(this->requestWidth_ == LAYOUT_WRAP_CONTENT){
            if(hasWeightWidgetList.empty()){
                this->width_ = totalWidgetWidth + paddingLeft_ + paddingRight_;
            }else{
                this->width_ = parentRequestWidth;
            }
        }//end if

        //set height
        if(requestHeight_ == LAYOUT_WRAP_CONTENT){
            height_ = std::min(maxWidgetHeight + paddingTop_ + paddingBottom_ , 
                                parentRequestHeight);
        }//end if
    }

    void RowContainer::onLayout(int l,int t) {
        this->Container::onLayout(l , t);

        int x = paddingLeft_ + left;
        int y = top - paddingTop_;

        for(auto widget: getChildrenWidgets()){
            if(widget == nullptr || widget->getVisible() == Gone){
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
                y = top - (this->height_ >> 1) + (widget->getHeight() >> 1);
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