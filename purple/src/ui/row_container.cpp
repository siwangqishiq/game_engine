#include "ui/row_container.h"
#include <algorithm>

namespace purple{

    void RowContainer::onMeasure(MeasureSpecMode widthSpecMode, 
                                int widthValue, 
                                MeasureSpecMode heightSpecMode,
                                int heightValue) {
        childWidgetMaxHeight = 0;
        childWidgetTotalWidth = 0;
        hasWeightWidgets.clear();

        setWidth(LAYOUT_UNSET);
        if(widthSpecMode == MeasureSpecMode::Exactly){
            setWidth(widthValue);
        }

        setHeight(LAYOUT_UNSET);
        if(heightSpecMode == MeasureSpecMode::Exactly){
            setHeight(heightValue);
        }

        measureChildWidgets(getWidth(), getHeight());
        
        bool needReMeasure = false;
        if(widthSpecMode == MeasureSpecMode::Atmost){
            setWidth(std::min(widthValue , childWidgetTotalWidth + getPaddingHorizontal()));
            needReMeasure = true;
        }
        if(heightSpecMode == MeasureSpecMode::Atmost){
            setHeight(std::min(heightValue , childWidgetMaxHeight + getPaddingVertial()));
            needReMeasure = true;
        }
        
        if(needReMeasure 
            && this->width_ != LAYOUT_UNSET
            && this->height_ != LAYOUT_UNSET){
            childWidgetTotalWidth = 0;
            measureChildWidgets(getWidth(), getHeight());
        }
    }

    void RowContainer::measureChildWidgets(int limitMaxWdith , int limitMaxHeight){
        for(auto pWidget : getChildrenWidgets()){
            if(pWidget == nullptr){
                continue;
            }
            
            MeasureSpecMode widthMode = MeasureSpecMode::Unset;
            int widthValue = 0;
            measureChildWidth(pWidget , widthMode , widthValue , limitMaxWdith);

            MeasureSpecMode heightMode = MeasureSpecMode::Unset;
            int heightValue = 0;
            measureChildHeight(pWidget , heightMode , heightValue , limitMaxHeight);

            pWidget->measure(widthMode , widthValue , heightMode , heightValue);

            const int costWidth = pWidget->getWidth() + pWidget->getMarginHorizontal();
            childWidgetTotalWidth += costWidth;
            
            const int costHeight = pWidget->getHeight() + pWidget->getMarginVertical();
            if(childWidgetMaxHeight < costHeight) {
                childWidgetMaxHeight = costHeight;
            }
        }//end for each

        measureWeightWidgets(limitMaxWdith, limitMaxHeight);
    }

    void RowContainer::measureWeightWidgets(int limitMaxWidth , int limitMaxHeight){
        if(hasWeightWidgets.empty()){
            return;
        }

        int totalWeightValue = 0;
        for(auto &pWidget : hasWeightWidgets){
            totalWeightValue += pWidget->getLayoutWeight();
        }//end for each

        const int remainWidth = getContentWidth() - childWidgetTotalWidth;
        if(remainWidth > 0 && totalWeightValue > 0){
            const int weightCube = remainWidth / totalWeightValue;
            for(auto &pWidget : hasWeightWidgets){
                MeasureSpecMode widthMode = MeasureSpecMode::Exactly;
                int widthValue = weightCube * pWidget->getLayoutWeight();

                MeasureSpecMode heightMode = MeasureSpecMode::Unset;
                int heightValue = 0;
                measureChildHeight(pWidget , heightMode , heightValue , limitMaxHeight);

                pWidget->measure(widthMode , widthValue , heightMode , heightValue);
            }//end for each
        }

        hasWeightWidgets.clear();
    }

    void RowContainer::measureChildWidth(PWidget widget, 
                MeasureSpecMode &outWidthMode, 
                int &outWidthValue,
                int limitMaxWdith) {
        const int reqWidth = widget->getRequestWidth();
        if(limitMaxWdith == LAYOUT_UNSET){ //父宽度未知
            if(reqWidth == LAYOUT_MATCH_PARENT){
                outWidthMode = MeasureSpecMode::Atmost;
                outWidthValue = WIDGET_MAX_WIDTH;
            }else if(reqWidth == LAYOUT_WRAP_CONTENT){
                outWidthMode = MeasureSpecMode::Atmost;
                outWidthValue = WIDGET_MAX_WIDTH;
            }else if(reqWidth == LAYOUT_UNSET){
                outWidthMode = MeasureSpecMode::Exactly;
                outWidthValue = 0;
            }else{
                outWidthMode = MeasureSpecMode::Exactly;
                outWidthValue = reqWidth;
            }
        }else{ //父宽度已知
            if(reqWidth == LAYOUT_MATCH_PARENT){
                outWidthMode = MeasureSpecMode::Exactly;
                outWidthValue = limitMaxWdith;
            }else if(reqWidth == LAYOUT_WRAP_CONTENT){
                outWidthMode = MeasureSpecMode::Atmost;
                outWidthValue = limitMaxWdith;
            }else if(reqWidth == LAYOUT_UNSET){
                outWidthMode = MeasureSpecMode::Exactly;
                outWidthValue = 0;
                if(widget->getLayoutWeight() > 0){
                    outWidthMode = MeasureSpecMode::Unset;
                    outWidthValue = 0;
                    hasWeightWidgets.emplace_back(widget);
                }
            }else{
                outWidthMode = MeasureSpecMode::Exactly;
                outWidthValue = reqWidth;
            }
        }
    }

    void RowContainer::measureChildHeight(PWidget widget, 
                            MeasureSpecMode &outHeightMode , 
                            int &outHeightValue,
                            int limitMaxHeight){
        const int reqHeight = widget->getRequestHeight();
        if(limitMaxHeight == LAYOUT_UNSET){//父控件高度未知
            if(reqHeight == LAYOUT_MATCH_PARENT){
                outHeightMode = MeasureSpecMode::Atmost;
                outHeightValue = WIDGET_MAX_HEIGHT;
            }else if(reqHeight == LAYOUT_WRAP_CONTENT){
                outHeightMode = MeasureSpecMode::Atmost;
                outHeightValue = WIDGET_MAX_HEIGHT;
            }else if(reqHeight == LAYOUT_UNSET){
                outHeightMode = MeasureSpecMode::Exactly;
                outHeightValue = 0;
            }else {
                outHeightMode = MeasureSpecMode::Exactly;
                outHeightValue = reqHeight;
            }
        }else{ //父控件高度已知
            if(reqHeight == LAYOUT_MATCH_PARENT){
                outHeightMode = MeasureSpecMode::Exactly;
                outHeightValue = limitMaxHeight;
            }else if(reqHeight == LAYOUT_WRAP_CONTENT){
                outHeightMode = MeasureSpecMode::Atmost;
                outHeightValue = limitMaxHeight;
            }else if(reqHeight == LAYOUT_UNSET){
                outHeightMode = MeasureSpecMode::Exactly;
                outHeightValue = 0;
            }else {
                outHeightMode = MeasureSpecMode::Exactly;
                outHeightValue = reqHeight;
            }
        }//end if
    }

    void RowContainer::onLayout(int l,int t) {
        this->Widget::onLayout(l , t);

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