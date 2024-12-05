
#include "ui/colum_container.h"
#include <limits>
#include <algorithm>


namespace purple{

    void ColumContainer::onMeasure(MeasureSpecMode widthSpecMode,int widthValue, 
                                MeasureSpecMode heightSpecMode,int heightValue){
        chidlWidgetMaxWidth = 0;
        childWidghtTotalHeight = 0;
        hasWeightWidgets_.clear();

        int limitMaxWidth = WIDGET_MAX_WIDTH;
        setWidth(LAYOUT_UNSET);
        if(widthSpecMode == MeasureSpecMode::Exactly){
            setWidth(widthValue);
        }else if(widthSpecMode == MeasureSpecMode::Atmost){
            limitMaxWidth = widthValue;
        }
        
        setHeight(LAYOUT_UNSET);
        int limitMaxHeight = WIDGET_MAX_HEIGHT;
        if(heightSpecMode == MeasureSpecMode::Exactly){
            setHeight(heightValue);
        }else if(widthSpecMode == MeasureSpecMode::Atmost){
            limitMaxHeight = heightValue;
        }

        measureChildWidgets(limitMaxWidth , limitMaxHeight);
        
        bool needReMeasure = false;
        if(this->width_ == LAYOUT_UNSET){
            setWidth(chidlWidgetMaxWidth + getPaddingHorizontal());
            needReMeasure = true;
        }

        if(this->height_ == LAYOUT_UNSET){
            setHeight(childWidghtTotalHeight + getPaddingVertial());
            needReMeasure = true;
        }

        if(needReMeasure 
            && this->width_ != LAYOUT_UNSET 
            && this->height_ != LAYOUT_UNSET){
            measureChildWidgets(limitMaxWidth , limitMaxHeight);
        }
    }

    void ColumContainer::measureChildWidgets(int limitMaxWidth, int limitMaxHeight) {
        for(auto &pWidget : getChildrenWidgets()){
            if(pWidget == nullptr){
                continue;
            }

            //width set
            MeasureSpecMode widthMode = MeasureSpecMode::Unset;
            int widthValue = 0;
            measureChildWidth(pWidget, limitMaxWidth, widthMode , widthValue);

            //height set
            MeasureSpecMode heightMode = MeasureSpecMode::Unset;
            int heightValue = 0;
            measureChildHeight(pWidget , limitMaxHeight ,heightMode , heightValue);
            
            //子widget 大小自测
            pWidget->measure(widthMode , widthValue , heightMode , heightValue);
            
            const int costWidth = pWidget->getWidth() + pWidget->getMarginHorizontal();
            if(chidlWidgetMaxWidth < costWidth){
                chidlWidgetMaxWidth = costWidth;
            }
            
            const int costHeight = pWidget->getHeight() + pWidget->getMarginVertical();
            childWidghtTotalHeight += costHeight;
        }//end for each
        
        measureWeightWidgets(limitMaxWidth , limitMaxHeight);
    }

    void ColumContainer::measureChildWidth(
            PWidget child, 
            int limitMaxwidth,
            MeasureSpecMode &mode , 
            int &value){
        const bool parentHasNotSetWidth = this->width_ == LAYOUT_UNSET;//父控件还未设置宽度

        if(parentHasNotSetWidth){//父控件宽度未确定
            if(child->getRequestWidth() == LAYOUT_MATCH_PARENT
                || child->getRequestWidth() == LAYOUT_WRAP_CONTENT){
                mode = MeasureSpecMode::Atmost;
                value = limitMaxwidth;
            }else if(child->getRequestWidth() == LAYOUT_UNSET){
                mode = MeasureSpecMode::Exactly;
                value = 0;
            }else{
                mode = MeasureSpecMode::Exactly;
                value = child->getRequestWidth();
            }
        }else{
            const int limitMaxWidth = 
                std::max(this->getWidth() - this->paddingLeft_ - this->paddingRight_ , 0);

            if(child->getRequestWidth() == LAYOUT_MATCH_PARENT){
                mode = MeasureSpecMode::Exactly;
                value = std::max(0, limitMaxWidth);
            }else if(child->getRequestWidth() == LAYOUT_WRAP_CONTENT){
                mode = MeasureSpecMode::Atmost;
                value = limitMaxWidth;
            }else if(child->getRequestWidth() == LAYOUT_UNSET){
                mode = MeasureSpecMode::Exactly;
                value = 0;
            }else{
                mode = MeasureSpecMode::Exactly;
                value = std::min(child->getRequestWidth() , limitMaxWidth);
            }
        }
    }

    void ColumContainer::measureChildHeight(
                            PWidget child,
                            int limitMaxHeight, 
                            MeasureSpecMode &mode , 
                            int &value){
        const bool parentNotSetHeight = this->height_ == LAYOUT_UNSET;//父控件还未设置高度
        if(parentNotSetHeight){//父控件高度未设置
            if(child->getRequestHeight() == LAYOUT_MATCH_PARENT
                || child->getRequestHeight() == LAYOUT_WRAP_CONTENT){
                mode = MeasureSpecMode::Atmost;
                value = limitMaxHeight;
            } else if(child->getRequestHeight() == LAYOUT_UNSET){
                mode = MeasureSpecMode::Exactly;
                value = 0;
            }else{
                mode = MeasureSpecMode::Exactly;
                value = std::min(child->getRequestHeight() , limitMaxHeight);
            }
        }else{ //父控件高度已经设置
            limitMaxHeight = std::max(this->getHeight() - this->getPaddingVertial() , 0);
            if(child->getRequestHeight() == LAYOUT_MATCH_PARENT){
                mode = MeasureSpecMode::Exactly;
                value = std::max(0, limitMaxHeight);
            }else if(child->getRequestHeight() == LAYOUT_WRAP_CONTENT){
                mode = MeasureSpecMode::Atmost;
                value = limitMaxHeight;
            }else if(child->getRequestHeight() == LAYOUT_UNSET){
                mode = MeasureSpecMode::Exactly;
                value = 0;
                if(child->getRequestHeight() > 0){ //设置了宽度权值  需要重新计算
                    mode = MeasureSpecMode::Unset;
                    value = 0;
                    this->hasWeightWidgets_.emplace_back(child);
                }
            }else{
                mode = MeasureSpecMode::Exactly;
                value = std::min(child->getRequestHeight() , limitMaxHeight);
            }
        }
    }

    void ColumContainer::measureWeightWidgets(int limitMaxWidth , int limitMaxHeight){
        if(hasWeightWidgets_.empty()){
            return;
        }

        const int currentCostHeight = childWidghtTotalHeight;
        const int remainTotal = std::max(getHeight() - currentCostHeight , 0);
        if(remainTotal > 0){
            int totalWeight = 0;
            for(auto &widget : hasWeightWidgets_){
                totalWeight += widget->getLayoutWeight();
            }//end for each

            if(totalWeight == 0){
                return;
            }

            const int cubeSize = remainTotal/totalWeight;
            for(auto &pWidget : hasWeightWidgets_){
                MeasureSpecMode widthMode = MeasureSpecMode::Unset;
                int widthValue = 0;
                measureChildWidth(pWidget, limitMaxWidth, widthMode , widthValue);

                MeasureSpecMode heightMode = MeasureSpecMode::Exactly;
                int heightValue = pWidget->getLayoutWeight() * cubeSize;
                pWidget->measure(widthMode , widthValue , heightMode , heightValue);//子widget 大小自测
            }//end for each
        }
        hasWeightWidgets_.clear();
    }

    void ColumContainer::onLayout(int l,int t){
        this->Widget::onLayout(l, t);

        int x = left;
        int y = top - paddingTop_;

        const int childLen = getChildrenWidgets().size();
        for(int i = 0; i < childLen; i++){
            PWidget child = getChildrenWidgets()[i];
            if(child == nullptr || child->getVisible() == Gone){
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
