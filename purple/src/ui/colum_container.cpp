
#include "ui/colum_container.h"
#include <limits>


namespace purple{

    void ColumContainer::measureChildWidgetSize(PWidget childWidget,
                        int limitWidth, 
                        int limitHeight){
        childWidget->measure(limitWidth , std::numeric_limits<int>::max());
    }

    void ColumContainer::measure(int parentRequestWidth , int parentRequestHeight){
        // Log::i("ui","ColumContainer measure...");

        int maxChildWidth = 0;
        int childTotalHeight = 0;
        for(PWidget &child: getChildrenWidgets()){
            //测量子布局
            measureChildWidgetSize(child,
                parentRequestWidth - paddingLeft_ - paddingRight_ 
                    - child->getMarginLeft()- child->getMarginRight(),0);

            if(maxChildWidth < child->getWidth()){
                maxChildWidth = child->getWidth();
            }
            childTotalHeight += (child->getHeight() + child->getMarginTop() + child->getMarginBottom());
        }//end for each


        //计算自身大小
        //self width
        if(requestWidth_ == LAYOUT_MATCH_PARENT){
            width_ = parentRequestWidth;
        }else if(this->requestWidth_ == LAYOUT_WRAP_CONTENT){
            width_ = paddingLeft_ + maxChildWidth + paddingRight_;
        }else{
            width_ = requestWidth_;
        }

        // self height
        if(this->requestHeight_ == LAYOUT_MATCH_PARENT){
            height_ = parentRequestHeight;
        }else if(this->requestHeight_ == LAYOUT_WRAP_CONTENT){
            height_ = paddingTop_ + childTotalHeight + paddingBottom_;
        }else{
            height_ = requestHeight_;
        }
    }

    void ColumContainer::layout(int l,int t){
        this->Widget::layout(l, t);

        int x = left;
        int y = top - paddingTop_;

        const int childLen = getChildrenWidgets().size();
        for(int i = 0; i < childLen; i++){
            PWidget child = getChildrenWidgets()[i];
            if(child == nullptr){
                continue;
            }

            const int childTop = y - child->getMarginTop();
            auto gravity = child->getLayoutGravity();
            if(gravity == LayoutGravity::TopCenter
                || gravity == LayoutGravity::Center
                || gravity == LayoutGravity::CenterLeft){
                child->layout(x + (width_ >> 1) - (child->getWidth() >> 1), childTop);
            }else if(gravity == LayoutGravity::TopRight 
                || gravity == LayoutGravity::CenterRight
                || gravity == LayoutGravity::BottomRight){
                child->layout(x + width_ - child->getWidth() - child->getMarginRight() - paddingRight_
                    , childTop);
            }else{
                child->layout(x + paddingLeft_ + child->getMarginLeft(),childTop);
            }
            
            y -= child->getMarginTop() + child->getHeight() + child->getMarginBottom();
        }//end for i
    }

    ColumContainer::~ColumContainer(){
        Log::i("widget","ColumContainer desstory");
    }
}
