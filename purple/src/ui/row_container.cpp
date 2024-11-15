

#include "ui/row_container.h"

namespace purple{

    void RowContainer::measure(int parentRequestWidth , int parentRequestHeight) {
        int maxWidgetHeight = 0;
        int totalWidgetWidth = 0;
        const auto childWidgets = getChildrenWidgets();
        for(auto widget: childWidgets){
            if(widget == nullptr){
                continue;
            }
            
            widget->measure(parentRequestWidth , parentRequestHeight);

            totalWidgetWidth += widget->getMarginLeft() + widget->getMarginRight() + widget->getWidth();
            if(maxWidgetHeight < widget->getHeight()){
                maxWidgetHeight = widget->getHeight();
            }
        }//end for each


        //set width
        if(this->requestWidth_ == LAYOUT_MATCH_PARENT){
            this->width_ = parentRequestWidth;
        }else if(this->requestWidth_ == LAYOUT_WRAP_CONTENT){
            this->width_ = totalWidgetWidth + paddingLeft_ + paddingRight_;
        }else {
            this->width_ = this->requestWidth_;
        }//endif

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
            
            widget->layout(x + widget->getMarginLeft() , y + widget->getMarginTop()); 
            x += widget->getMarginLeft() + widget->getMarginRight() + widget->getWidth();
        }//end for each
    }


    RowContainer::~RowContainer(){
        
    }
}